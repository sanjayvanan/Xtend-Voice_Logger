#include "dashboard.h"
#include "ui_dashboard.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>

Dashboard::Dashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dashboard),
    apiHandler(new APIHandler(this))
{
    ui->setupUi(this);

    // Connect API handler signals
    connect(apiHandler, &APIHandler::callDetailsReceived,
            this, &Dashboard::handleCallDetails);
    connect(apiHandler, &APIHandler::callDetailsFailed,
            this, &Dashboard::handleCallDetailsFailed);
    connect(apiHandler, &APIHandler::liveCallsReceived,
            this, &Dashboard::handleLiveCalls);
    connect(apiHandler, &APIHandler::liveCallsFailed,
            this, &Dashboard::handleLiveCallsFailed);
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::setSessionToken(const QString &token)
{
    sessionToken = token;
    if (!sessionToken.isEmpty()) {
        // Start periodic updates
        updateDashboard();
        // Set up timer for periodic updates
        QTimer *updateTimer = new QTimer(this);
        connect(updateTimer, &QTimer::timeout, this, &Dashboard::updateDashboard);
        updateTimer->start(5000); // Update every 5 seconds
    }
}

void Dashboard::updateDashboard()
{
    // Get today's date range
    QDateTime startOfDay = QDateTime::currentDateTime();
    startOfDay.setTime(QTime(0, 0, 0));
    QDateTime endOfDay = startOfDay.addDays(1).addSecs(-1);

    // Fetch today's call details
    apiHandler->fetchCallList(
        sessionToken,
        startOfDay,
        endOfDay,
        "", // callerNo
        "", // callType
        0,  // pageNumber
        1000 // pageSize
    );

    // Fetch live calls
    apiHandler->fetchLiveCalls(sessionToken);
}

void Dashboard::handleCallDetails(const QJsonObject &details)
{
    QJsonArray callList = details["List"].toArray();
    
    // Initialize counters
    int totalCalls = callList.size();
    int connectedCalls = 0;
    int missedCalls = 0;
    int incomingCalls = 0;
    int outgoingCalls = 0;

    // Process each call
    for (const QJsonValue &callVal : callList) {
        QJsonObject call = callVal.toObject();
        
        // Count by status
        QString status = call["Call-Status"].toString();
        if (status == "Connected") {
            connectedCalls++;
        } else if (status == "Missed" || status == "No Answer") {
            missedCalls++;
        }

        // Count by type
        QString callType = call["Call-Type"].toString();
        if (callType == "I") {
            incomingCalls++;
        } else if (callType == "O") {
            outgoingCalls++;
        }
    }

    // Update UI labels
    ui->labelTodayTotal->setText(QString("Total Calls: %1").arg(totalCalls));
    ui->labelTodayConnected->setText(QString("Connected: %1").arg(connectedCalls));
    ui->labelTodayMissed->setText(QString("Missed: %1").arg(missedCalls));
    ui->labelTodayIncoming->setText(QString("Incoming: %1").arg(incomingCalls));
    ui->labelTodayOutgoing->setText(QString("Outgoing: %1").arg(outgoingCalls));
}

void Dashboard::handleCallDetailsFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch call details: " + message);
}

void Dashboard::handleLiveCalls(const QJsonObject &details)
{
    QJsonArray callList = details["List"].toArray();
    
    int activeCalls = callList.size();
    int activeIncoming = 0;
    int activeOutgoing = 0;

    // Process live calls
    for (const QJsonValue &callVal : callList) {
        QJsonObject call = callVal.toObject();
        QString callType = call["Call-Type"].toString();
        
        if (callType == "I") {
            activeIncoming++;
        } else if (callType == "O") {
            activeOutgoing++;
        }
    }

    // Update UI labels
    ui->labelActiveCalls->setText(QString("Active Calls: %1").arg(activeCalls));
    ui->labelActiveIncoming->setText(QString("Active Incoming: %1").arg(activeIncoming));
    ui->labelActiveOutgoing->setText(QString("Active Outgoing: %1").arg(activeOutgoing));
}

void Dashboard::handleLiveCallsFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch live calls: " + message);
}
