#ifndef LIVECALLS_H
#define LIVECALLS_H

#include <QWidget>
#include "apihandler.h"
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTemporaryFile>
#include <QMap>

namespace Ui {
class LiveCalls;
}

class LiveCalls : public QWidget
{
    Q_OBJECT

public:
    explicit LiveCalls(QWidget *parent = nullptr);
    ~LiveCalls();
    void setSessionToken(const QString &token);
    void setCurrentUser(const QString &username);
    void startMonitoring();
    void stopMonitoring();

private slots:
    void updateLiveCalls();
    void handleLiveCalls(const QJsonObject &details);
    void handleLiveCallsFailed(const QString &message);
    void onChannelGroupChanged(int index);
    void handleWaveFile(const QByteArray &waveData);

private:
    Ui::LiveCalls *ui;
    APIHandler *apiHandler;
    QString sessionToken;
    QString currentUsername;
    QTimer *updateTimer;
    
    // Channel group filtering
    QMap<QString, QStringList> channelGroups;
    void loadChannelGroups();
    void filterCallsByChannelGroup(QJsonArray &callList);
    QTimer *liveCallsTimer;
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;
    QTemporaryFile *tempWaveFile;
    void updateLiveCallsTable(const QJsonObject &details);
};

#endif // LIVECALLS_H
