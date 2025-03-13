#include "timetimecalls.h"
#include "ui_timetimecalls.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QJsonArray>
#include <QDebug>
#include <QMediaPlayer>
#include <QTemporaryFile>
#include <QPushButton>
#include <QFile>
#include <QAudioOutput>
#include <QDir>
#include "audioplayerdialog.h"
#include <QDateTime>
#include "usermanagement.h"
#include <QSqlQuery>
#include "mainwindow.h"

TimeTimeCalls::TimeTimeCalls(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimeTimeCalls)
    , apiHandler(new APIHandler(this))
    , mediaPlayer(new QMediaPlayer(this))
    , tempWaveFile(nullptr)
    , totalPages(0)
{
    ui->setupUi(this);
    
    // Initialize date/time fields
    initializeDateTimeFields();
    
    // Connect API handler signals
    connect(apiHandler, &APIHandler::callDetailsReceived, this, &TimeTimeCalls::handleCallDetails);
    connect(apiHandler, &APIHandler::callDetailsFailed, this, &TimeTimeCalls::handleCallDetailsFailed);
    connect(apiHandler, &APIHandler::waveFileReceived, this, &TimeTimeCalls::handleWaveFile);
    connect(apiHandler, &APIHandler::waveFileFailed, this, &TimeTimeCalls::handleWaveFileFailed);
    
    // Connect table cell clicked signal
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &TimeTimeCalls::handleTableCellClicked);
    
    // Connect channel group combo box change signal
    connect(ui->channelGroupCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TimeTimeCalls::onChannelGroupChanged, Qt::UniqueConnection);
    
    // Set up audio output for media player
    QAudioOutput *audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    
    // Load channel groups
    loadChannelGroups();
}

TimeTimeCalls::~TimeTimeCalls()
{
    delete ui;
    delete mediaPlayer;
    delete tempWaveFile;
}

void TimeTimeCalls::initializeDateTimeFields()
{
    // Set the from date to start of current day
    QDateTime startOfDay = QDateTime::currentDateTime();
    startOfDay.setTime(QTime(0, 0));
    ui->fromDateTime->setDateTime(startOfDay);
    
    // Set the to date to current date/time
    ui->toDateTime->setDateTime(QDateTime::currentDateTime());
    
    // Set default values
    ui->pageSize->setValue(50);
    ui->currentPage->setValue(1);
}

void TimeTimeCalls::loadChannelGroups()
{
    // Clear the combo box first
    ui->channelGroupCombo->clear();
    
    // Get the current username from the main window
    QString currentUsername;
    QWidget* parent = this->parentWidget();
    while (parent) {
        MainWindow* mainWindow = qobject_cast<MainWindow*>(parent);
        if (mainWindow) {
            currentUsername = mainWindow->getCurrentUsername();
            break;
        }
        parent = parent->parentWidget();
    }
    
    // If we couldn't get the username, return
    if (currentUsername.isEmpty()) {
        return;
    }
    
    // Check if user is admin
    bool isAdmin = UserManagement::isUserAdmin(currentUsername);
    
    // Get all channel groups
    QList<QPair<QString, QStringList>> allGroups = UserManagement::getChannelGroups();
    
    if (isAdmin) {
        // Admin can see all channel groups and has the "All" option
        ui->channelGroupCombo->addItem("All");
        
        for (const auto &group : allGroups) {
            ui->channelGroupCombo->addItem(group.first);
            channelGroups[group.first] = group.second;
        }
    } else {
        // Regular user can only see assigned channel groups
        QSqlQuery query;
        query.prepare("SELECT cg.group_name, cg.channels FROM user_channel_groups ucg "
                     "JOIN channel_groups cg ON ucg.group_name = cg.group_name "
                     "WHERE ucg.username = :username");
        query.bindValue(":username", currentUsername);
        
        if (query.exec()) {
            while (query.next()) {
                QString groupName = query.value(0).toString();
                QString channelsStr = query.value(1).toString();
                QStringList channels = channelsStr.split(",", Qt::SkipEmptyParts);
                
                ui->channelGroupCombo->addItem(groupName);
                channelGroups[groupName] = channels;
            }
        }
        
        // If no channel groups are assigned, add a placeholder
        if (ui->channelGroupCombo->count() == 0) {
            ui->channelGroupCombo->addItem("No assigned channels");
            ui->channelGroupCombo->setEnabled(false);
        }
    }
    
    // Select the first item
    if (ui->channelGroupCombo->count() > 0) {
        ui->channelGroupCombo->setCurrentIndex(0);
    }
}

void TimeTimeCalls::refreshChannelGroups()
{
    loadChannelGroups();
}

void TimeTimeCalls::setSessionToken(const QString &token)
{
    sessionToken = token;
    if (!sessionToken.isEmpty() && isVisible()) {
        performSearch();  // Perform initial search if widget is visible
    }
}

void TimeTimeCalls::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    
    // Refresh channel groups when shown
    loadChannelGroups();
    
    if (!sessionToken.isEmpty()) {
        performSearch();  // Perform search when widget becomes visible
    }
}

void TimeTimeCalls::on_searchButton_clicked()
{
    if (sessionToken.isEmpty()) {
        QMessageBox::warning(this, "Error", "No active session");
        return;
    }

    // Reset pagination to first page when searching
    ui->currentPage->setValue(1);
    performSearch();
}

void TimeTimeCalls::handleCallDetails(const QJsonObject &details)
{
    // Store the call details for filtering
    lastCallDetails = details;
    
    // Update the table with the call details
    updateCallDetailsTable(details);
}

void TimeTimeCalls::filterCallsByChannelGroup(QJsonArray &callList)
{
    // Get the selected channel group
    QString selectedGroup = ui->channelGroupCombo->currentText();
    
    // If "All" is selected or no channel groups are available, return all calls
    if (selectedGroup == "All" || !channelGroups.contains(selectedGroup)) {
        return;
    }
    
    // Get the channels for the selected group
    QStringList channels = channelGroups[selectedGroup];
    
    // Filter the call list
    QJsonArray filteredList;
    for (int i = 0; i < callList.size(); i++) {
        QJsonObject call = callList[i].toObject();
        QString channel = call["Channel"].toString();
        
        if (channels.contains(channel)) {
            filteredList.append(call);
        }
    }
    
    // Replace the original list with the filtered one
    callList = filteredList;
}

void TimeTimeCalls::handleCallDetailsFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch call details: " + message);
}

void TimeTimeCalls::updateCallDetailsTable(const QJsonObject &details)
{
    // Get the call list
    QJsonArray callList = details["List"].toArray();
    
    // Filter calls by channel group
    filterCallsByChannelGroup(callList);
    
    // Clear the table
    ui->tableWidget->setRowCount(0);
    
    // Update total calls count
    int totalCalls = callList.size();
    ui->labelTotalCalls->setText("Total Connected Calls: " + QString::number(totalCalls));
    
    // Update pagination controls
    updatePaginationControls(totalCalls);
    
    // Populate the table with call details
    for (int i = 0; i < callList.size(); i++) {
        QJsonObject call = callList[i].toObject();
        
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        
        // Play button - Use the correct key "CallRef-ID"
        QPushButton *playButton = new QPushButton("Play", ui->tableWidget);
        playButton->setProperty("callRefId", call["CallRef-ID"].toString());
        playButton->setProperty("wavPass", call["Wav-Pass"].toString());
        connect(playButton, &QPushButton::clicked, this, [this, playButton]() {
            QString callRefId = playButton->property("callRefId").toString();
            QString wavPass = playButton->property("wavPass").toString();
            apiHandler->streamWaveFile(sessionToken, callRefId, wavPass);
        });
        ui->tableWidget->setCellWidget(row, 0, playButton);
        
        // Set other columns
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(call["Channel"].toString()));
        
        // Determine which ID to display
        QString displayId;
        if (call.contains("Called-ID") && !call["Called-ID"].toString().isEmpty()) {
            displayId = call["Called-ID"].toString();
        } else if (call.contains("Caller-ID") && !call["Caller-ID"].toString().isEmpty()) {
            displayId = call["Caller-ID"].toString();
        } else {
            displayId = call["CallRef-ID"].toString();
        }
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(displayId)); // Display ID
        
        // Call Type (I/O to Incoming/Outgoing)
        QString callType = call["Call-Type"].toString();
        if (callType == "I") {
            callType = "Incoming";
        } else if (callType == "O") {
            callType = "Outgoing";
        }
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(callType));
        
        // Call Status
        QString callStatus = call["Call-Status"].toString();
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(callStatus));
        
        // Format call time
        QString callTimeStr = call["Call-Time"].toString();
        QDateTime callTime = QDateTime::fromString(callTimeStr, "yyyyMMddhhmmss");
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(callTime.toString("yyyy-MM-dd hh:mm:ss")));
        
        // Duration - Use Connect-Duration for the duration column
        QString duration = call["Connect-Duration"].toString();
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(duration));
        
        // Ring Duration
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(call["Ring-Duration"].toString()));
        
        // Connect Duration
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(call["Connect-Duration"].toString()));
        
        // Compression
        ui->tableWidget->setItem(row, 9, new QTableWidgetItem(call["Compression"].toString()));
        
        // Channel Hardware
        ui->tableWidget->setItem(row, 10, new QTableWidgetItem(call["Channel-Hardware"].toString()));
    }
    
    // Add debug output to check the JSON structure
    qDebug() << "First call in list:" << (callList.size() > 0 ? callList[0].toObject() : QJsonObject());
}

void TimeTimeCalls::handleTableCellClicked(int row, int column)
{
    // This can be removed or left empty since we're handling clicks through the button
}

void TimeTimeCalls::handleWaveFile(const QByteArray &waveData)
{
    qDebug() << "Received wave data, size:" << waveData.size();

    // Create a temporary file to store the wave data
    if (tempWaveFile) {
        delete tempWaveFile;
    }
    tempWaveFile = new QTemporaryFile(this);
    tempWaveFile->setFileTemplate(QDir::tempPath() + "/voicelogger_XXXXXX.wav");
    
    if (!tempWaveFile->open()) {
        QMessageBox::warning(this, "Error", "Could not create temporary file for playback");
        return;
    }

    // Write the wave data to the temporary file
    tempWaveFile->write(waveData);
    tempWaveFile->flush();
    tempWaveFile->seek(0);

    qDebug() << "Created temporary file:" << tempWaveFile->fileName();

    // Create and show the audio player dialog
    AudioPlayerDialog *playerDialog = new AudioPlayerDialog(this);
    playerDialog->setTitle("Call Recording");
    playerDialog->setAudioSource(tempWaveFile->fileName());
    playerDialog->exec();

    delete playerDialog;
}

void TimeTimeCalls::handleWaveFileFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch wave file: " + message);
}

void TimeTimeCalls::performSearch()
{
    QString callType;
    switch(ui->callTypeCombo->currentIndex()) {
        case 1: callType = "I"; break; // Incoming
        case 2: callType = "O"; break; // Outgoing
        default: callType = ""; break; // All
    }

    int currentPageValue = ui->currentPage->value() - 1; // API uses 0-based indexing
    
    // Always fetch all data from API (without channel filtering)
    apiHandler->fetchCallList(
        sessionToken,
        ui->fromDateTime->dateTime(),
        ui->toDateTime->dateTime(),
        ui->phoneNumber->text(),
        callType,
        currentPageValue,
        ui->pageSize->value()
    );
    
    // The filtering by channel group will be done in handleCallDetails
}

void TimeTimeCalls::updatePaginationControls(int totalCalls)
{
    int pageSize = ui->pageSize->value();
    totalPages = (totalCalls + pageSize - 1) / pageSize;
    
    ui->currentPage->setMaximum(totalPages);
    ui->btnPrevPage->setEnabled(ui->currentPage->value() > 1);
    ui->btnNextPage->setEnabled(ui->currentPage->value() < totalPages);
}

void TimeTimeCalls::on_btnPrevPage_clicked()
{
    if (ui->currentPage->value() > 1) {
        ui->currentPage->setValue(ui->currentPage->value() - 1);
        performSearch();
    }
}

void TimeTimeCalls::on_btnNextPage_clicked()
{
    if (ui->currentPage->value() < totalPages) {
        ui->currentPage->setValue(ui->currentPage->value() + 1);
        performSearch();
    }
}

void TimeTimeCalls::on_currentPage_valueChanged(int value)
{
    ui->btnPrevPage->setEnabled(value > 1);
    ui->btnNextPage->setEnabled(value < totalPages);
    
    // Only perform search if the widget is visible
    if (isVisible()) {
        performSearch();
    }
}

void TimeTimeCalls::onChannelGroupChanged(int index)
{
    // If we have stored call details, update the table with the new filter
    if (!lastCallDetails.isEmpty()) {
        updateCallDetailsTable(lastCallDetails);
    }
}

