#ifndef TIMETIMECALLS_H
#define TIMETIMECALLS_H

#include <QWidget>
#include <QDateTime>
#include "apihandler.h"
#include <QMediaPlayer>
#include <QTemporaryFile>
#include <QAudioOutput>
#include <QDir>

namespace Ui {
class TimeTimeCalls;
}

class TimeTimeCalls : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTimeCalls(QWidget *parent = nullptr);
    ~TimeTimeCalls();
    void setSessionToken(const QString &token);
    void refreshChannelGroups();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_searchButton_clicked();
    void on_btnPrevPage_clicked();
    void on_btnNextPage_clicked();
    void on_currentPage_valueChanged(int value);
    void handleCallDetails(const QJsonObject &details);
    void handleCallDetailsFailed(const QString &message);
    void updateCallDetailsTable(const QJsonObject &details);
    void handleTableCellClicked(int row, int column);
    void handleWaveFile(const QByteArray &waveData);
    void handleWaveFileFailed(const QString &message);

private:
    void performSearch();
    void updatePaginationControls(int totalCalls);
    void initializeDateTimeFields();
    void loadChannelGroups();
    void filterCallsByChannelGroup(QJsonArray &callList);
    
    Ui::TimeTimeCalls *ui;
    APIHandler *apiHandler;
    QString sessionToken;
    QMediaPlayer *mediaPlayer;
    QTemporaryFile *tempWaveFile;
    int totalPages;
    
    // Channel group filtering
    QMap<QString, QStringList> channelGroups;
    QJsonObject lastCallDetails; // Store the last call details for filtering
};

#endif // TIMETIMECALLS_H
