#include "dashboard.h"
#include "ui_dashboard.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

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
        apiHandler->fetchCallDetails(sessionToken, "");
        apiHandler->fetchLiveCalls(sessionToken);
    }
}

void Dashboard::handleCallDetails(const QJsonObject &details)
{
    updateStatistics(details, QJsonObject());
}

void Dashboard::handleCallDetailsFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch call details: " + message);
}

void Dashboard::handleLiveCalls(const QJsonObject &details)
{
    updateStatistics(QJsonObject(), details);
}

void Dashboard::handleLiveCallsFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch live calls: " + message);
}

void Dashboard::updateStatistics(const QJsonObject &callDetails, const QJsonObject &liveDetails)
{
    // Update total calls
    if (!callDetails.isEmpty()) {
        QJsonArray callList = callDetails["List"].toArray();
        ui->labelTotalCalls->setText(QString("Total Calls: %1").arg(callList.size()));
        
        // Count connected calls
        int connectedCalls = 0;
        for (const QJsonValue &call : callList) {
            if (call.toObject()["Call-Status"].toString() == "Connected") {
                connectedCalls++;
            }
        }
        ui->labelConnectedCalls->setText(QString("Connected Calls: %1").arg(connectedCalls));
    }

    // Update active calls
    if (!liveDetails.isEmpty()) {
        ui->labelActiveCalls->setText(QString("Active Calls: %1").arg(liveDetails["TotalCount"].toString()));
    }
}
