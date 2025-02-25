#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "apihandler.h"
#include "timetimecalls.h"
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTemporaryFile>
#include "dashboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSessionToken(const QString &token);

private slots:
    void on_actionLogout_triggered();
    void handleLogoutSuccess();
    void handleLogoutFailure(const QString &message);
    void handleCallDetails(const QJsonObject &details);
    void handleCallDetailsFailed(const QString &message);
    void handleLiveCalls(const QJsonObject &details);
    void handleLiveCallsFailed(const QString &message);
    void updateLiveCallsTable(const QJsonObject &details);
    void refreshLiveCalls();
    void handleWaveFile(const QByteArray &waveData);

    void on_btnDashboard_clicked();

    void on_btnCallLogs_clicked();

    void on_btnLiveCalls_clicked();

private:
    Ui::MainWindow *ui;
    APIHandler *apiHandler;
    QString sessionToken;
    TimeTimeCalls *timeTimeCalls;
    QTimer *liveCallsTimer;
    QMediaPlayer *mediaPlayer = nullptr;
    QAudioOutput *audioOutput = nullptr;
    QTemporaryFile *tempWaveFile = nullptr;
    Dashboard *dashboard;
    void updateCallDetailsTable(const QJsonObject &details);
};
#endif // MAINWINDOW_H
