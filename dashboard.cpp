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
    apiHandler(new APIHandler(this)),
    totalCalls(0),          // Initialize totalCalls
    connectedCalls(0),      // Initialize connectedCalls
    missedCalls(0),         // Initialize missedCalls
    incomingCalls(0),       // Initialize incomingCalls
    outgoingCalls(0)        // Initialize outgoingCalls
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
        // Trigger immediate update
        updateDashboard();
        
        // Set up timer for periodic updates (every 5 seconds)
        QTimer *updateTimer = new QTimer(this);
        connect(updateTimer, &QTimer::timeout, this, &Dashboard::updateDashboard);
        updateTimer->start(5000);
    }
}

void Dashboard::updateDashboard()
{
    if (!sessionToken.isEmpty()) {
        // Get current date/time
        QDateTime now = QDateTime::currentDateTime();
        QDateTime startOfDay = QDateTime(now.date(), QTime(0, 0, 0));
        
        // Fetch today's call details
        apiHandler->fetchCallList(sessionToken, startOfDay, now);
        
        // Fetch live calls
        apiHandler->fetchLiveCalls(sessionToken);
    }
}

void Dashboard::handleCallDetails(const QJsonObject &details)
{
    QJsonArray callList = details["List"].toArray();
    
    // Reset counters
    totalCalls = callList.size(); // Use class member variable
    connectedCalls = 0; // Use class member variable
    missedCalls = 0; // Use class member variable
    incomingCalls = 0; // Use class member variable
    outgoingCalls = 0; // Use class member variable

    // Process each call
    for (const QJsonValue &callVal : callList) {
        QJsonObject call = callVal.toObject();
        
        // Count by status
        QString status = call["Call-Status"].toString();
        if (status == "Connected") {
            connectedCalls++;
        } else if (status == "Missed" || status == "No Answer" || status == "Missed Call") { // Include "Missed Call"
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

void Dashboard::updateStatistics(const QJsonObject &callDetails, const QJsonObject &liveDetails)
{
    // Process call list
    QJsonArray callList = callDetails["List"].toArray();
    for (const QJsonValue &callVal : callList) {
        QJsonObject call = callVal.toObject();
        QString callType = call["Call-Type"].toString();
        QString callStatus = call["Call-Status"].toString();

        totalCalls++;

        // Update connected and missed calls count
        if (callStatus == "Connected") {
            connectedCalls++;
        } else if (callStatus == "Missed" || callStatus == "No Answer" || callStatus == "Failed") {
            missedCalls++; // Ensure to include all relevant statuses for missed calls
        }

        // Update incoming/outgoing count
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
