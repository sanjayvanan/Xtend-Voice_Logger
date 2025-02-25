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
{
    ui->setupUi(this);

    // Initialize date/time editors with default values
    QDateTime now = QDateTime::currentDateTime();
    ui->fromDateTime->setDateTime(now.addDays(-1));
    ui->toDateTime->setDateTime(now);

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
}

TimeTimeCalls::~TimeTimeCalls()
{
    delete ui;
    delete mediaPlayer;
    delete tempWaveFile;
}

void TimeTimeCalls::setSessionToken(const QString &token)
{
    sessionToken = token;
}

void TimeTimeCalls::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    if (!sessionToken.isEmpty()) {
        performSearch();
    }
}

void TimeTimeCalls::performSearch()
{
    QString callType;
    switch(ui->callTypeCombo->currentIndex()) {
        case 1: callType = "I"; break;
        case 2: callType = "O"; break;
        default: break;
    }

    apiHandler->fetchCallList(
        sessionToken,
        ui->fromDateTime->dateTime(),
        ui->toDateTime->dateTime(),
        ui->phoneNumber->text(),
        callType,
        0,
        ui->pageSize->value()
    );
}

void TimeTimeCalls::on_searchButton_clicked()
{
    if (sessionToken.isEmpty()) {
        QMessageBox::warning(this, "Error", "No active session");
        return;
    }

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
        QString channelName = call["Channel-Name"].toString();
        QString channelHardware = call["Channel-Hardware"].toString();
        QString callType = call["Call-Type"].toString();
        QString callTime = call["Call-Time"].toString();
        QString totalDuration = call["Total-Duration"].toString();
        QString ringDuration = call["Ring-Duration"].toString();
        QString connectDuration = call["Connect-Duration"].toString();
        QString callStatus = call["Call-Status"].toString();
        QString compression = call["Compression"].toString();

        // Determine which ID to display
        QString displayId = !callerId.isEmpty() ? callerId : (!calledId.isEmpty() ? calledId : refId);
        QTableWidgetItem *refIdItem = new QTableWidgetItem(displayId);
        QTableWidgetItem *channelItem = new QTableWidgetItem(channel);
        QTableWidgetItem *channelNameItem = new QTableWidgetItem(channelName);
        QTableWidgetItem *channelHardwareItem = new QTableWidgetItem(channelHardware);
        QTableWidgetItem *callTypeItem = new QTableWidgetItem(callType);
        QTableWidgetItem *callTimeItem = new QTableWidgetItem(callTime);
        QTableWidgetItem *totalDurationItem = new QTableWidgetItem(totalDuration);
        QTableWidgetItem *ringDurationItem = new QTableWidgetItem(ringDuration);
        QTableWidgetItem *connectDurationItem = new QTableWidgetItem(connectDuration);
        QTableWidgetItem *callStatusItem = new QTableWidgetItem(callStatus);
        QTableWidgetItem *compressionItem = new QTableWidgetItem(compression);

        ui->tableWidget->setItem(row, 0, refIdItem);
        ui->tableWidget->setItem(row, 1, channelItem);
        ui->tableWidget->setItem(row, 2, channelNameItem);
        ui->tableWidget->setItem(row, 3, channelHardwareItem);
        ui->tableWidget->setItem(row, 4, callTypeItem);
        ui->tableWidget->setItem(row, 5, callTimeItem);
        ui->tableWidget->setItem(row, 6, totalDurationItem);
        ui->tableWidget->setItem(row, 7, ringDurationItem);
        ui->tableWidget->setItem(row, 8, connectDurationItem);
        ui->tableWidget->setItem(row, 9, callStatusItem);
        ui->tableWidget->setItem(row, 10, compressionItem);

        // Create Play button
        QPushButton *playButton = new QPushButton("Play");
        QString audioFile = call["Audio-File"].toString();
        
        // Fix the file path by replacing single backslashes with double backslashes or forward slashes
        audioFile.replace("\\", "/");
        
        qDebug() << "Original audio file path:" << call["Audio-File"].toString();
        qDebug() << "Processed audio file path:" << audioFile;

        playButton->setProperty("audioFile", audioFile);
        playButton->setProperty("callRefId", call["CallRef-ID"].toString());
        
        // Connect button click to play function
        connect(playButton, &QPushButton::clicked, this, [this, playButton]() {
            QString audioFile = playButton->property("audioFile").toString();
            QString callRefId = playButton->property("callRefId").toString();
            
            QFile file(audioFile);
            if (!audioFile.isEmpty() && file.exists()) {
                qDebug() << "Local file found, attempting to play...";
                if (!mediaPlayer) {
                    mediaPlayer = new QMediaPlayer(this);
                    // Add an audio output device
                    QAudioOutput *audioOutput = new QAudioOutput(this);
                    mediaPlayer->setAudioOutput(audioOutput);
                }
                mediaPlayer->setSource(QUrl::fromLocalFile(audioFile));
                mediaPlayer->play();
            } else {
                apiHandler->streamWaveFile(sessionToken, callRefId);
            }
        });

        ui->tableWidget->setCellWidget(row, 11, playButton);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSortingEnabled(true);
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

