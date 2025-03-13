#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include "apihandler.h"
#include <QTimer>

namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();
    void setSessionToken(const QString &token);
    void setCurrentUser(const QString &username);
    void startMonitoring();
    void stopMonitoring();

private slots:
    void handleCallDetails(const QJsonObject &details);
    void handleCallDetailsFailed(const QString &message);
    void handleLiveCalls(const QJsonObject &details);
    void handleLiveCallsFailed(const QString &message);
    void updateDashboard();
    void updateStatistics(const QJsonObject &callDetails, const QJsonObject &liveDetails);
    void refreshUserAssignedChannels();

private:
    Ui::Dashboard *ui;
    APIHandler *apiHandler;
    QString sessionToken;
    QString currentUsername;
    QTimer *updateTimer;
    QStringList assignedChannels;

    // Declare the variables to track call statistics
    int totalCalls = 0;
    int connectedCalls = 0;
    int missedCalls = 0;
    int incomingCalls = 0;
    int outgoingCalls = 0;
    
    // Helper method to filter calls by assigned channels
    void filterCallsByAssignedChannels(QJsonArray &callList);
};

#endif // DASHBOARD_H
