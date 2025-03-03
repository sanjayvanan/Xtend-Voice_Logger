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
    updateTimer(new QTimer(this)),
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

    // Set up timer for periodic updates
    connect(updateTimer, &QTimer::timeout, this, &Dashboard::updateDashboard);
    updateTimer->setInterval(5000); // 5 seconds
}

Dashboard::~Dashboard()
{
    stopMonitoring();
    delete ui;
}

void Dashboard::setSessionToken(const QString &token)
{
    sessionToken = token;
    if (!sessionToken.isEmpty()) {
        startMonitoring();
    }
}

void Dashboard::startMonitoring()
{
    // Trigger immediate update
    updateDashboard();
    // Start periodic updates
    updateTimer->start();
}

void Dashboard::stopMonitoring()
{
    updateTimer->stop();
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
    totalCalls = callList.size();
    connectedCalls = 0;
    missedCalls = 0;
    incomingCalls = 0;
    outgoingCalls = 0;

    // Process each call
    for (const QJsonValue &callVal : callList) {
        QJsonObject call = callVal.toObject();
        
        // Count by status
        QString status = call["Call-Status"].toString();
        if (status == "Connected") {
            connectedCalls++;
        } else if (status == "Missed" || status == "No Answer" || status == "Missed Call") {
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

    // Update UI with modern stats display
    ui->labelStatTotal->setText(QString::number(totalCalls));
    ui->labelStatConnected->setText(QString::number(connectedCalls));
    ui->labelStatMissed->setText(QString::number(missedCalls));
    
    // Update progress bars for call types
    int maxCalls = qMax(incomingCalls, outgoingCalls);
    if (maxCalls > 0) {
        ui->progressIncoming->setMaximum(maxCalls);
        ui->progressOutgoing->setMaximum(maxCalls);
    } else {
        ui->progressIncoming->setMaximum(1);
        ui->progressOutgoing->setMaximum(1);
    }
    
    ui->progressIncoming->setValue(incomingCalls);
    ui->progressOutgoing->setValue(outgoingCalls);
    
    // Update progress bars for call status
    int maxStatus = qMax(connectedCalls, missedCalls);
    if (maxStatus > 0) {
        ui->progressConnected->setMaximum(maxStatus);
        ui->progressMissed->setMaximum(maxStatus);
    } else {
        ui->progressConnected->setMaximum(1);
        ui->progressMissed->setMaximum(1);
    }
    
    ui->progressConnected->setValue(connectedCalls);
    ui->progressMissed->setValue(missedCalls);
}

void Dashboard::handleCallDetailsFailed(const QString &message)
{
   qDebug() << "Error fetching call details:" << message;
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

    // Update UI labels for live status
    ui->labelStatActive->setText(QString::number(activeCalls));
    ui->labelLiveIncoming->setText(QString::number(activeIncoming));
    ui->labelLiveOutgoing->setText(QString::number(activeOutgoing));
}

void Dashboard::handleLiveCallsFailed(const QString &message)
{
    // QMessageBox::warning(this, "Error", "Failed to fetch live calls: " + message);
    qDebug() << "Error fetching call details:" << message;
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

    // Update UI labels using existing labels
    ui->labelStatTotal->setText(QString("Total Calls: %1").arg(totalCalls));
    ui->labelStatConnected->setText(QString("Connected: %1").arg(connectedCalls));
    ui->labelStatMissed->setText(QString("Missed: %1").arg(missedCalls));
    ui->labelLiveIncoming->setText(QString("Incoming: %1").arg(incomingCalls));
    ui->labelLiveOutgoing->setText(QString("Outgoing: %1").arg(outgoingCalls));
}
