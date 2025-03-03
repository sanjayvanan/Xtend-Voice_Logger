#include "livecalls.h"
#include "ui_livecalls.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <QDir>

LiveCalls::LiveCalls(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LiveCalls)
    , apiHandler(new APIHandler(this))
    , liveCallsTimer(new QTimer(this))
    , mediaPlayer(nullptr)
    , audioOutput(nullptr)
    , tempWaveFile(nullptr)
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
            this, &LiveCalls::refreshLiveCalls);
}

void LiveCalls::startMonitoring()
{
    if (!sessionToken.isEmpty()) {
        refreshLiveCalls(); // Fetch immediately
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
    if (!token.isEmpty()) {
        startMonitoring(); // Start monitoring when token is set
    }
}

void LiveCalls::refreshLiveCalls()
{
    if (!sessionToken.isEmpty()) {
        apiHandler->fetchLiveCalls(sessionToken);
    }
}

void LiveCalls::handleLiveCalls(const QJsonObject &details)
{
    updateLiveCallsTable(details);
}

void LiveCalls::handleLiveCallsFailed(const QString &message)
{
    ui->labelStatus->setText("Error: " + message);
}

void LiveCalls::updateLiveCallsTable(const QJsonObject &details)
{
    // Clear existing items
    ui->tableLiveCalls->clearContents();
    ui->tableLiveCalls->setRowCount(0);

    // Update status label
    QString status = details["status"].toString();
    QString message = details["message"].toString();

    if (status == "0") {
        ui->labelStatus->setText("No active calls");
        return;
    }

    QJsonArray callList = details["List"].toArray();
    ui->tableLiveCalls->setRowCount(callList.size());
    ui->labelStatus->setText(QString("Active Calls: %1").arg(callList.size()));

    for (int i = 0; i < callList.size(); ++i) {
        QJsonObject call = callList[i].toObject();

        // Create table items
        QTableWidgetItem *channel = new QTableWidgetItem(call["Channel"].toString());
        QTableWidgetItem *channelName = new QTableWidgetItem(call["Channel-Name"].toString());
        QTableWidgetItem *callType = new QTableWidgetItem(call["Call-Type"].toString() == "O" ? "Outgoing" : "Incoming");
        QTableWidgetItem *callTime = new QTableWidgetItem(call["Call-Time"].toString());
        QTableWidgetItem *callerID = new QTableWidgetItem(call["Caller-ID"].toString());
        QTableWidgetItem *calledID = new QTableWidgetItem(call["Called-ID"].toString());
        QTableWidgetItem *reason = new QTableWidgetItem(call["Reason"].toString());

        // Set items in table
        ui->tableLiveCalls->setItem(i, 0, channel);
        ui->tableLiveCalls->setItem(i, 1, channelName);
        ui->tableLiveCalls->setItem(i, 2, callType);
        ui->tableLiveCalls->setItem(i, 3, callTime);
        ui->tableLiveCalls->setItem(i, 4, callerID);
        ui->tableLiveCalls->setItem(i, 5, calledID);
        ui->tableLiveCalls->setItem(i, 6, reason);

        // Add Listen button for connected calls
        if (call["Reason"].toString() == "Connected") {
            QPushButton *listenButton = new QPushButton("Listen Live");
            listenButton->setProperty("callRefId", call["CallRef-ID"].toString());
            
            connect(listenButton, &QPushButton::clicked, this, [this, call]() {
                QString callRefId = call["CallRef-ID"].toString();
                apiHandler->streamWaveFile(sessionToken, callRefId);
            });

            ui->tableLiveCalls->setCellWidget(i, 7, listenButton);
        }
    }

    ui->tableLiveCalls->resizeColumnsToContents();
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

LiveCalls::~LiveCalls()
{
    stopMonitoring();
    delete ui;
    if (tempWaveFile) {
        delete tempWaveFile;
    }
}
