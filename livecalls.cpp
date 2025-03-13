#include "livecalls.h"
#include "ui_livecalls.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>
#include <QComboBox>
#include <QSqlQuery>
#include <QDateTime>
#include "mainwindow.h"
#include "usermanagement.h"

LiveCalls::LiveCalls(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LiveCalls)
    , apiHandler(new APIHandler(this))
    , liveCallsTimer(new QTimer(this))
    , mediaPlayer(nullptr)
    , audioOutput(nullptr)
    , tempWaveFile(nullptr)
    , updateTimer(new QTimer(this))
    , currentUsername("")
{
    ui->setupUi(this);
    
    // Connect API handler signals
    connect(apiHandler, &APIHandler::liveCallsReceived,
            this, &LiveCalls::handleLiveCalls);
    connect(apiHandler, &APIHandler::liveCallsFailed,
            this, &LiveCalls::handleLiveCallsFailed);
    connect(apiHandler, &APIHandler::waveFileReceived,
            this, &LiveCalls::handleWaveFile);

    // Set up timer for live calls refresh
    liveCallsTimer->setInterval(5000); // Refresh every 5 seconds
    connect(liveCallsTimer, &QTimer::timeout,
            this, &LiveCalls::updateLiveCalls);

    // Set up update timer
    updateTimer->setInterval(3000); // Update every 3 seconds
    connect(updateTimer, &QTimer::timeout,
            this, &LiveCalls::updateLiveCalls);
    
    // Connect channel group combo box change signal if it exists
    if (ui->channelGroupCombo) {
        connect(ui->channelGroupCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &LiveCalls::onChannelGroupChanged, Qt::UniqueConnection);
    }
}

void LiveCalls::startMonitoring()
{
    if (!sessionToken.isEmpty()) {
        updateLiveCalls(); // Fetch immediately
        liveCallsTimer->start(); // Start periodic updates
    }
}

void LiveCalls::stopMonitoring()
{
    liveCallsTimer->stop();
}

void LiveCalls::setSessionToken(const QString &token)
{
    sessionToken = token;
    
    // Load channel groups when session token is set
    loadChannelGroups();
    
    // Start monitoring
    if (!sessionToken.isEmpty() && !updateTimer->isActive()) {
        updateTimer->start(3000); // Update every 3 seconds
    }
}

void LiveCalls::setCurrentUser(const QString &username)
{
    currentUsername = username;
    
    // Reload channel groups when user changes
    loadChannelGroups();
}

void LiveCalls::loadChannelGroups()
{
    // Check if the UI has a channelGroupCombo
    if (!ui->channelGroupCombo) {
        // If not found, we can't continue
        return;
    }
    
    // Clear the combo box first
    ui->channelGroupCombo->clear();
    
    // If no username is set, try to get it from the main window
    if (currentUsername.isEmpty()) {
        QWidget* parent = this->parentWidget();
        while (parent) {
            MainWindow* mainWindow = qobject_cast<MainWindow*>(parent);
            if (mainWindow) {
                currentUsername = mainWindow->getCurrentUsername();
                break;
            }
            parent = parent->parentWidget();
        }
    }
    
    // If we still couldn't get the username, return
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

void LiveCalls::onChannelGroupChanged(int index)
{
    // Refresh the live calls display with the new filter
    updateLiveCalls();
}

void LiveCalls::filterCallsByChannelGroup(QJsonArray &callList)
{
    // Check if the UI has a channelGroupCombo
    if (!ui->channelGroupCombo) {
        return;
    }
    
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

void LiveCalls::handleLiveCalls(const QJsonObject &details)
{
    // Get the call list
    QJsonArray callList = details["List"].toArray();
    
    // Filter calls by channel group
    filterCallsByChannelGroup(callList);
    
    // Clear the table
    ui->tableLiveCalls->setRowCount(0);
    
    // Update total calls count
    int totalCalls = callList.size();
    ui->labelStatus->setText("Total Active Calls: " + QString::number(totalCalls));
    
    // Populate the table with call details
    for (int i = 0; i < callList.size(); i++) {
        QJsonObject call = callList[i].toObject();
        
        int row = ui->tableLiveCalls->rowCount();
        ui->tableLiveCalls->insertRow(row);
        
        // Set columns
        ui->tableLiveCalls->setItem(row, 0, new QTableWidgetItem(call["Channel"].toString()));
        ui->tableLiveCalls->setItem(row, 1, new QTableWidgetItem(call["Channel-Name"].toString()));
        
        // Call Type (I/O to Incoming/Outgoing)
        QString callType = call["Call-Type"].toString();
        if (callType == "I") {
            callType = "Incoming";
        } else if (callType == "O") {
            callType = "Outgoing";
        }
        ui->tableLiveCalls->setItem(row, 2, new QTableWidgetItem(callType));
        
        // Call Time
        QString callTimeStr = call["Call-Time"].toString();
        QDateTime callTime = QDateTime::fromString(callTimeStr, "yyyyMMddhhmmss");
        ui->tableLiveCalls->setItem(row, 3, new QTableWidgetItem(callTime.toString("yyyy-MM-dd hh:mm:ss")));
        
        // Call Ref ID - Make sure to use the correct key
        ui->tableLiveCalls->setItem(row, 4, new QTableWidgetItem(call["Call-Ref-ID"].toString()));
        
        // Duration - Make sure to use the correct key
        ui->tableLiveCalls->setItem(row, 5, new QTableWidgetItem(call["Duration"].toString()));
        
        // Caller ID
        ui->tableLiveCalls->setItem(row, 6, new QTableWidgetItem(call["Caller-ID"].toString()));
        
        // Called ID
        ui->tableLiveCalls->setItem(row, 7, new QTableWidgetItem(call["Called-ID"].toString()));
        
        // Reason
        ui->tableLiveCalls->setItem(row, 8, new QTableWidgetItem(call["Reason"].toString()));
        
        // Add Listen button for connected calls
        if (call["Reason"].toString() == "Connected") {
            QPushButton *listenButton = new QPushButton("Listen Live");
            listenButton->setProperty("callRefId", call["Call-Ref-ID"].toString());
            
            connect(listenButton, &QPushButton::clicked, this, [this, call]() {
                QString callRefId = call["Call-Ref-ID"].toString();
                apiHandler->streamWaveFile(sessionToken, callRefId);
            });

            ui->tableLiveCalls->setCellWidget(row, 9, listenButton);
        }
    }

    ui->tableLiveCalls->resizeColumnsToContents();
}

void LiveCalls::handleLiveCallsFailed(const QString &message)
{
    ui->labelStatus->setText("Error: " + message);
}

void LiveCalls::handleWaveFile(const QByteArray &waveData)
{
    if (!mediaPlayer) {
        mediaPlayer = new QMediaPlayer(this);
        audioOutput = new QAudioOutput(this);
        mediaPlayer->setAudioOutput(audioOutput);
    }

    // Create a temporary file for the streaming audio
    if (tempWaveFile) {
        delete tempWaveFile;
    }
    tempWaveFile = new QTemporaryFile(this);
    tempWaveFile->setFileTemplate(QDir::tempPath() + "/voicelogger_live_XXXXXX.wav");

    if (!tempWaveFile->open()) {
        QMessageBox::warning(this, "Error", "Could not create temporary file for playback");
        return;
    }

    // Write the wave data and play
    tempWaveFile->write(waveData);
    tempWaveFile->flush();
    tempWaveFile->seek(0);

    mediaPlayer->setSource(QUrl::fromLocalFile(tempWaveFile->fileName()));
    mediaPlayer->play();
}

void LiveCalls::updateLiveCalls()
{
    if (!sessionToken.isEmpty()) {
        apiHandler->fetchLiveCalls(sessionToken);
    }
}

LiveCalls::~LiveCalls()
{
    stopMonitoring();
    delete ui;
    if (tempWaveFile) {
        delete tempWaveFile;
    }
}
