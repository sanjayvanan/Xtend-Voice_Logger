#ifndef TIMETIMECALLS_H
#define TIMETIMECALLS_H

#include <QWidget>
#include <QDateTime>
#include "apihandler.h"
#include <QMediaPlayer>
#include <QTemporaryFile>
#include <QAudioOutput>
#include <QDir>
#include <QCalendarWidget>
#include <QCompleter>
#include <QStringListModel>

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
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_searchButton_clicked();
    void on_btnPrevPage_clicked();
    void on_btnNextPage_clicked();
    void handleCallDetails(const QJsonObject &details);
    void handleCallDetailsFailed(const QString &message);
    void updateCallDetailsTable(const QJsonObject &details);
    void handleTableCellClicked(int row, int column);
    void handleWaveFile(const QByteArray &waveData);
    void handleWaveFileFailed(const QString &message);
    void onChannelGroupChanged(int index);
    void showFromDateCalendar();
    void showToDateCalendar();
    void onFromDateSelected();
    void onToDateSelected();

private:
    void performSearch();
    void updatePaginationControls(int totalCalls);
    void initializeDateTimeFields();
    void loadChannelGroups();
    void filterCallsByChannelGroup(QJsonArray &callList);
    void applyClientSidePagination(const QJsonArray &filteredList);
    
    Ui::TimeTimeCalls *ui;
    APIHandler *apiHandler;
    QString sessionToken;
    QMediaPlayer *mediaPlayer;
    QTemporaryFile *tempWaveFile;
    int totalPages;
    int currentPage = 1; // Track current page for row numbering
    
    // Calendar widgets
    QCalendarWidget *fromDateCalendar;
    QCalendarWidget *toDateCalendar;
    
    // Channel group filtering
    QMap<QString, QStringList> channelGroups;
    QJsonObject lastCallDetails; // Store the last call details for filtering
    
    // New methods for phone number autocomplete
    void setupPhoneNumberAutocomplete();
    void updatePhoneNumberSuggestions();
    QStringList fetchUniquePhoneNumbers();
    
    // New member variables
    QCompleter *phoneCompleter;
    QStringListModel *phoneNumbersModel;
};

#endif // TIMETIMECALLS_H
