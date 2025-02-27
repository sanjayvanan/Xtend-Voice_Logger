#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>


class APIHandler : public QObject
{
    Q_OBJECT

public:
    explicit APIHandler(QObject *parent = nullptr);
    void login(const QString &username, const QString &hashedPassword);
    void logout(const QString &token);
    void fetchCallDetails(const QString &token, const QString &callRefId);
    void fetchCallList(const QString &token, 
                      const QDateTime &fromDate,
                      const QDateTime &toDate,
                      const QString &callerNo = QString(),
                      const QString &callType = QString(),
                      int pageNumber = 0,
                      int pageSize = 50);
    void fetchLiveCalls(const QString &token);
    void streamWaveFile(const QString &token, const QString &callRefId, const QString &wavPass = QString());
    static QString hashPassword(const QString &password);

signals:
    void loginSuccessful(const QString &token);
    void loginFailed(const QString &message);
    void logoutSuccessful();
    void logoutFailed(const QString &message);
    void callDetailsReceived(const QJsonObject &details);
    void callDetailsFailed(const QString &message);
    void liveCallsReceived(const QJsonObject &details);
    void liveCallsFailed(const QString &message);
    void waveFileReceived(const QByteArray &waveData);
    void waveFileFailed(const QString &message);

private slots:
    void onLoginReply(QNetworkReply *reply);
    void onLogoutReply(QNetworkReply *reply);
    void onCallDetailsReply(QNetworkReply *reply);
    void onLiveCallsReply(QNetworkReply *reply);
    void onWaveFileReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    const QString baseUrl = "http://127.0.0.1:8080/WebAPI.xbc";
};

#endif // APIHANDLER_H
