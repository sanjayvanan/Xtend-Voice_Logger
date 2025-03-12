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

TimeTimeCalls::TimeTimeCalls(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimeTimeCalls)
    , apiHandler(new APIHandler(this))
    , mediaPlayer(nullptr)
    , tempWaveFile(nullptr)
    , totalPages(1)
{
    ui->setupUi(this);
    
    // Initialize date/time fields
    initializeDateTimeFields();
    
    // Connect API handler signals
    connect(apiHandler, &APIHandler::callDetailsReceived,
            this, &TimeTimeCalls::handleCallDetails);
    connect(apiHandler, &APIHandler::callDetailsFailed,
            this, &TimeTimeCalls::handleCallDetailsFailed);
    connect(apiHandler, &APIHandler::waveFileReceived,
            this, &TimeTimeCalls::handleWaveFile);
    connect(apiHandler, &APIHandler::waveFileFailed,
            this, &TimeTimeCalls::handleWaveFileFailed);

    // Connect table cell clicked signal
    connect(ui->tableWidget, &QTableWidget::cellClicked,
            this, &TimeTimeCalls::handleTableCellClicked);

    // Set up the table widget
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Initialize pagination controls
    ui->currentPage->setValue(1);
    ui->btnPrevPage->setEnabled(false);
    ui->btnNextPage->setEnabled(false);
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
    updateCallDetailsTable(details);
}

void TimeTimeCalls::handleCallDetailsFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch call details: " + message);
}

void TimeTimeCalls::updateCallDetailsTable(const QJsonObject &details)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    if (!details.contains("List")) {
        qDebug() << "No 'List' field in response";
        return;
    }

    QJsonArray callList = details["List"].toArray();
    QString totalCount = details["TotalCount"].toString("0");
    ui->labelTotalCalls->setText(QString("Total Connected Calls: %1").arg(totalCount));

    ui->tableWidget->setSortingEnabled(false);
    
    for (const QJsonValue &callValue : callList) {
        QJsonObject call = callValue.toObject();
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        // Create and set table items
        QString refId = call["CallRef-ID"].toString();
        QString callerId = call["Caller-ID"].toString();
        QString calledId = call["Called-ID"].toString();
        QString channel = call["Channel"].toString();
        QString callType = call["Call-Type"].toString();
        QString callStatus = call["Call-Status"].toString();
        QString callTime = call["Call-Time"].toString();
        QString totalDuration = call["Total-Duration"].toString();
        QString ringDuration = call["Ring-Duration"].toString();
        QString connectDuration = call["Connect-Duration"].toString();
        QString compression = call["Compression"].toString();
        QString channelHardware = call["Channel-Hardware"].toString();

        // Format Call Time from YYYYMMDDHHMMSS to yyyy-MM-dd HH:mm:ss
        if (callTime.length() == 14) { // Ensure the length is correct
            QString year = callTime.mid(0, 4);
            QString month = callTime.mid(4, 2);
            QString day = callTime.mid(6, 2);
            QString hour = callTime.mid(8, 2);
            QString minute = callTime.mid(10, 2);
            QString second = callTime.mid(12, 2);
            callTime = QString("%1-%2-%3 %4:%5:%6").arg(year, month, day, hour, minute, second);
        } else {
            callTime = "Invalid Date"; // Handle invalid date format
        }

        // Determine which ID to display
        QString displayId = !callerId.isEmpty() ? callerId : (!calledId.isEmpty() ? calledId : refId);

        // Create table items
        QTableWidgetItem *playButtonItem = new QTableWidgetItem("Play");
        QTableWidgetItem *channelItem = new QTableWidgetItem(channel);
        QTableWidgetItem *refIdItem = new QTableWidgetItem(displayId);
        QTableWidgetItem *callTypeItem = new QTableWidgetItem(callType);
        QTableWidgetItem *callStatusItem = new QTableWidgetItem(callStatus);
        QTableWidgetItem *callTimeItem = new QTableWidgetItem(callTime);
        QTableWidgetItem *totalDurationItem = new QTableWidgetItem(totalDuration);
        QTableWidgetItem *ringDurationItem = new QTableWidgetItem(ringDuration);
        QTableWidgetItem *connectDurationItem = new QTableWidgetItem(connectDuration);
        QTableWidgetItem *compressionItem = new QTableWidgetItem(compression);
        QTableWidgetItem *channelHardwareItem = new QTableWidgetItem(channelHardware);

        // Set items in the new order
        ui->tableWidget->setItem(row, 0, playButtonItem); // Play
        ui->tableWidget->setItem(row, 1, channelItem); // Channel
        ui->tableWidget->setItem(row, 2, refIdItem); // Call Ref ID
        ui->tableWidget->setItem(row, 3, callTypeItem); // Call Type
        ui->tableWidget->setItem(row, 4, callStatusItem); // Call Status
        ui->tableWidget->setItem(row, 5, callTimeItem); // Call Time
        ui->tableWidget->setItem(row, 6, totalDurationItem); // Duration
        ui->tableWidget->setItem(row, 7, ringDurationItem); // Ring Duration
        ui->tableWidget->setItem(row, 8, connectDurationItem); // Connect Duration
        ui->tableWidget->setItem(row, 9, compressionItem); // Compression
        ui->tableWidget->setItem(row, 10, channelHardwareItem); // Channel Hardware

        // Create Play button
        QPushButton *playButton = new QPushButton("Play");
        QString audioFile = call["Audio-File"].toString();
        
        // Fix the file path by replacing single backslashes with double backslashes or forward slashes
        audioFile.replace("\\", "/");
        
        playButton->setProperty("audioFile", audioFile);
        playButton->setProperty("callRefId", call["CallRef-ID"].toString());
        
        // Connect button click to play function
        connect(playButton, &QPushButton::clicked, this, [this, playButton]() {
            QString audioFile = playButton->property("audioFile").toString();
            QString callRefId = playButton->property("callRefId").toString();
            
            QFile file(audioFile);
            if (!audioFile.isEmpty() && file.exists()) {
                if (!mediaPlayer) {
                    mediaPlayer = new QMediaPlayer(this);
                    QAudioOutput *audioOutput = new QAudioOutput(this);
                    mediaPlayer->setAudioOutput(audioOutput);
                }
                mediaPlayer->setSource(QUrl::fromLocalFile(audioFile));
                mediaPlayer->play();
            } else {
                apiHandler->streamWaveFile(sessionToken, callRefId);
            }
        });

        ui->tableWidget->setCellWidget(row, 0, playButton); // Set Play button in the first column
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSortingEnabled(true);

    // Update pagination
    updatePaginationControls(totalCount.toInt());
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
    
    apiHandler->fetchCallList(
        sessionToken,
        ui->fromDateTime->dateTime(),
        ui->toDateTime->dateTime(),
        ui->phoneNumber->text(),
        callType, 
        currentPageValue,
        ui->pageSize->value()
    );
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

