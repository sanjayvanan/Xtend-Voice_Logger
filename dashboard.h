#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include "apihandler.h"

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

private slots:
    void handleCallDetails(const QJsonObject &details);
    void handleCallDetailsFailed(const QString &message);
    void handleLiveCalls(const QJsonObject &details);
    void handleLiveCallsFailed(const QString &message);

private:
    Ui::Dashboard *ui;
    APIHandler *apiHandler;
    QString sessionToken;
    void updateDashboard();
    void updateStatistics(const QJsonObject &callDetails, const QJsonObject &liveDetails);
};

#endif // DASHBOARD_H
