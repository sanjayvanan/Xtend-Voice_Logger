#include "timetimecalls.h"
#include "ui_timetimecalls.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QJsonArray>
#include <QDebug>
#include <QMediaPlayer>
#include <QTemporaryFile>
#include <QPushButton>
#include <QFile>
#include <QAudioOutput>
#include <QDir>
#include "audioplayerdialog.h"
#include <QDateTime>
#include "usermanagement.h"
#include <QSqlQuery>
#include "mainwindow.h"
#include <QCalendarWidget>
#include <QCompleter>
#include <QStringListModel>
#include <QSet>
#include <QTimer>

TimeTimeCalls::TimeTimeCalls(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimeTimeCalls)
    , apiHandler(new APIHandler(this))
    , mediaPlayer(new QMediaPlayer(this))
    , tempWaveFile(nullptr)
    , totalPages(0)
    , phoneCompleter(nullptr)
    , phoneNumbersModel(new QStringListModel(this))
{
    ui->setupUi(this);
    
    // Enable sorting for the table widget
    ui->tableWidget->setSortingEnabled(true);
    
    // Check if pageSize is available in the UI - some debug info
    if (!ui->pageSize) {
        qDebug() << "WARNING: pageSize combo box not found in UI!";
    } else {
        qDebug() << "Page size combo found with" << ui->pageSize->count() << "items";
        
        // Check if page size items need to be added (in case they're not in UI file)
        if (ui->pageSize->count() == 0) {
            ui->pageSize->addItem("20");
            ui->pageSize->addItem("40");
            ui->pageSize->addItem("60");
            ui->pageSize->addItem("80");
            ui->pageSize->addItem("100");
        }
    }
    
    // Initialize date/time fields
    initializeDateTimeFields();
    
    // Connect API handler signals
    connect(apiHandler, &APIHandler::callDetailsReceived, this, &TimeTimeCalls::handleCallDetails);
    connect(apiHandler, &APIHandler::callDetailsFailed, this, &TimeTimeCalls::handleCallDetailsFailed);
    connect(apiHandler, &APIHandler::waveFileReceived, this, &TimeTimeCalls::handleWaveFile);
    connect(apiHandler, &APIHandler::waveFileFailed, this, &TimeTimeCalls::handleWaveFileFailed);
    
    // Connect table cell clicked signal
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &TimeTimeCalls::handleTableCellClicked);
    
    // Connect channel group combo box change signal
    connect(ui->channelGroupCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TimeTimeCalls::onChannelGroupChanged, Qt::UniqueConnection);
    
    // Set up audio output for media player
    QAudioOutput *audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    
    // Load channel groups
    loadChannelGroups();
    
    // Initialize calendar widgets
    fromDateCalendar = new QCalendarWidget(this);
    fromDateCalendar->setWindowFlags(Qt::Popup);
    fromDateCalendar->hide();
    
    toDateCalendar = new QCalendarWidget(this);
    toDateCalendar->setWindowFlags(Qt::Popup);
    toDateCalendar->hide();
    
    // Connect calendar signals
    connect(fromDateCalendar, &QCalendarWidget::clicked, this, &TimeTimeCalls::onFromDateSelected);
    connect(toDateCalendar, &QCalendarWidget::clicked, this, &TimeTimeCalls::onToDateSelected);
    
    // Connect date edit click events to show calendars
    ui->fromDateTime->installEventFilter(this);
    ui->toDateTime->installEventFilter(this);
    
    // Optional: Remove complex styles to see if it resolves the dropdown issue
    // fromDateCalendar->setStyleSheet(""); // Clear any custom styles
    // toDateCalendar->setStyleSheet(""); // Clear any custom styles
    
    // Connect page size change event - make sure this works properly
    connect(ui->pageSize, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
        // Handle page size change
        if (!lastCallDetails.isEmpty()) {
            ui->currentPage->setText("1"); // Reset to page 1
            QJsonArray callList = lastCallDetails["List"].toArray();
            filterCallsByChannelGroup(callList);
            applyClientSidePagination(callList);
        }
    });
    
    // Connect editable combo box text changed event
    connect(ui->pageSize->lineEdit(), &QLineEdit::editingFinished, this, [this]() {
        // Get the new page size
        bool ok = false;
        int newSize = ui->pageSize->currentText().toInt(&ok);
        
        // Validate and update
        if (ok && newSize > 0) {
            if (!lastCallDetails.isEmpty()) {
                ui->currentPage->setText("1"); // Reset to page 1
                QJsonArray callList = lastCallDetails["List"].toArray();
                filterCallsByChannelGroup(callList);
                applyClientSidePagination(callList);
            }
        } else {
            // Invalid input, reset to 50
            ui->pageSize->setCurrentText("50");
        }
    });
    
    // Set up phone number autocomplete
    setupPhoneNumberAutocomplete();
    
    // Connect date fields to update phone number suggestions
    connect(ui->fromDateTime, &QDateTimeEdit::dateTimeChanged, this, &TimeTimeCalls::updatePhoneNumberSuggestions);
    connect(ui->toDateTime, &QDateTimeEdit::dateTimeChanged, this, &TimeTimeCalls::updatePhoneNumberSuggestions);
}

TimeTimeCalls::~TimeTimeCalls()
{
    delete ui;
    delete mediaPlayer;
    delete tempWaveFile;
}

void TimeTimeCalls::initializeDateTimeFields()
{
    // Set the from date to start of current day
    QDateTime startOfDay = QDateTime::currentDateTime();
    startOfDay.setTime(QTime(0, 0));
    ui->fromDateTime->setDateTime(startOfDay);
    
    // Set the to date to current date/time
    ui->toDateTime->setDateTime(QDateTime::currentDateTime());
    
    // Set default values - ensure the page size has a proper default value
    ui->pageSize->setCurrentIndex(2); // Select the 3rd item (60)
    ui->currentPage->setText("1");
}

void TimeTimeCalls::loadChannelGroups()
{
    // Clear the combo box first
    ui->channelGroupCombo->clear();
    
    // Get the current username from the main window
    QString currentUsername;
    QWidget* parent = this->parentWidget();
    while (parent) {
        MainWindow* mainWindow = qobject_cast<MainWindow*>(parent);
        if (mainWindow) {
            currentUsername = mainWindow->getCurrentUsername();
            break;
        }
        parent = parent->parentWidget();
    }
    
    // If we couldn't get the username, return
    if (currentUsername.isEmpty()) {
        return;
    }
    
    // Check if user is admin
    bool isAdmin = UserManagement::isUserAdmin(currentUsername);
    
    // Get all channel groups
    QList<QPair<QString, QStringList>> allGroups = UserManagement::getChannelGroups();
    
    if (isAdmin) {
        // Admin can see all channel groups and has the "All" option
        ui->channelGroupCombo->addItem("All");
        
        for (const auto &group : allGroups) {
            ui->channelGroupCombo->addItem(group.first);
            channelGroups[group.first] = group.second;
        }
    } else {
        // Regular user can only see assigned channel groups
        QSqlQuery query;
        query.prepare("SELECT cg.group_name, cg.channels FROM user_channel_groups ucg "
                     "JOIN channel_groups cg ON ucg.group_name = cg.group_name "
                     "WHERE ucg.username = :username");
        query.bindValue(":username", currentUsername);
        
        if (query.exec()) {
            while (query.next()) {
                QString groupName = query.value(0).toString();
                QString channelsStr = query.value(1).toString();
                QStringList channels = channelsStr.split(",", Qt::SkipEmptyParts);
                
                ui->channelGroupCombo->addItem(groupName);
                channelGroups[groupName] = channels;
            }
        }
        
        // If no channel groups are assigned, add a placeholder
        if (ui->channelGroupCombo->count() == 0) {
            ui->channelGroupCombo->addItem("No assigned channels");
            ui->channelGroupCombo->setEnabled(false);
            
            // Disable search button for users with no assigned channels
            ui->searchButton->setEnabled(false);
        } else {
            ui->searchButton->setEnabled(true);
        }
    }
    
    // Select the first item
    if (ui->channelGroupCombo->count() > 0) {
        ui->channelGroupCombo->setCurrentIndex(0);
    }
}

void TimeTimeCalls::refreshChannelGroups()
{
    loadChannelGroups();
}

void TimeTimeCalls::setSessionToken(const QString &token)
{
    sessionToken = token;
    
    // Reset search criteria when setting a new session token (after login)
    initializeDateTimeFields();
    ui->phoneNumber->clear();
    ui->callTypeCombo->setCurrentIndex(0); // Reset to "All"
    ui->currentPage->setText("1");
    
    // Clear any previous search results
    ui->tableWidget->setRowCount(0);
    lastCallDetails = QJsonObject();
    
    if (!sessionToken.isEmpty() && isVisible()) {
        performSearch();  // Perform initial search if widget is visible
    }
}

void TimeTimeCalls::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    
    // Refresh channel groups when shown
    loadChannelGroups();
    
    if (!sessionToken.isEmpty()) {
        performSearch();  // Perform search when widget becomes visible
    }
}

void TimeTimeCalls::on_searchButton_clicked()
{
    if (sessionToken.isEmpty()) {
        QMessageBox::warning(this, "Error", "No active session");
        return;
    }

    // Reset pagination to first page when searching
    ui->currentPage->setText("1");
    
    // If the phone number is empty after a search, update the suggestions
    if (ui->phoneNumber->text().isEmpty()) {
        updatePhoneNumberSuggestions();
    }
    
    performSearch();
}

void TimeTimeCalls::handleCallDetails(const QJsonObject &details)
{
    // Store the original call details
    lastCallDetails = details;
    
    // Get the original call list
    QJsonArray callList = details["List"].toArray();
    
    // Store the original count before filtering
    int originalTotalCalls = 0;
    if (details.contains("TotalCount")) {
        originalTotalCalls = details["TotalCount"].toString().toInt();
    } else {
        originalTotalCalls = callList.size();
    }
    
    // Filter calls by channel group
    filterCallsByChannelGroup(callList);
    
    // After filtering, apply client-side pagination
    applyClientSidePagination(callList);
}

void TimeTimeCalls::filterCallsByChannelGroup(QJsonArray &callList)
{
    // Get the selected channel group
    QString selectedGroup = ui->channelGroupCombo->currentText();
    
    // If "No assigned channels" is selected, clear the list
    if (selectedGroup == "No assigned channels") {
        callList = QJsonArray(); // Clear the list
        return;
    }
    
    // If "All" is selected and user is admin, return all calls
    if (selectedGroup == "All") {
        // Get the current username from the main window
        QString currentUsername;
        QWidget* parent = this->parentWidget();
        while (parent) {
            MainWindow* mainWindow = qobject_cast<MainWindow*>(parent);
            if (mainWindow) {
                currentUsername = mainWindow->getCurrentUsername();
                break;
            }
            parent = parent->parentWidget();
        }
        
        // Only admins should see all calls
        if (UserManagement::isUserAdmin(currentUsername)) {
            return;
        }
    }
    
    // If a specific channel group is selected, filter by those channels
    if (channelGroups.contains(selectedGroup)) {
        QStringList channels = channelGroups[selectedGroup];
        
        // Filter the call list
        QJsonArray filteredList;
        for (int i = 0; i < callList.size(); i++) {
            QJsonObject call = callList[i].toObject();
            QString channel = call["Channel"].toString();
            
            if (channels.contains(channel)) {
                filteredList.append(call);
            }
        }
        
        // Replace the original list with the filtered one
        callList = filteredList;
    }
}

void TimeTimeCalls::handleCallDetailsFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch call details: " + message);
}

void TimeTimeCalls::updateCallDetailsTable(const QJsonObject &details)
{
    // Get the call list
    QJsonArray callList = details["List"].toArray();
    
    // Store the original count before filtering
    int originalTotalCalls = 0;
    if (details.contains("TotalCount")) {
        originalTotalCalls = details["TotalCount"].toString().toInt();
    } else {
        originalTotalCalls = callList.size();
    }
    
    // Filter calls by channel group
    filterCallsByChannelGroup(callList);
    
    // Clear the table
    ui->tableWidget->setRowCount(0);
    
    // Update total calls count - use filtered count when a specific channel group is selected
    QString selectedGroup = ui->channelGroupCombo->currentText();
    int totalCalls = 0;
    
    if (selectedGroup == "All" || !channelGroups.contains(selectedGroup)) {
        // If "All" is selected, use the original total count
        totalCalls = originalTotalCalls;
    } else {
        // If a specific channel group is selected, use the filtered count
        totalCalls = callList.size();
    }
    
    ui->labelTotalCalls->setText("Total Connected Calls: " + QString::number(totalCalls));
    
    // Update pagination controls - use filtered count for pagination when a specific channel group is selected
    updatePaginationControls(totalCalls);
    
    // Check if we have any data
    if (callList.isEmpty()) {
        // Display "No available data" message
        ui->tableWidget->setRowCount(1);
        QTableWidgetItem* noDataItem = new QTableWidgetItem("No available data");
        noDataItem->setTextAlignment(Qt::AlignCenter);
        
        // Create a font for the message
        QFont font = noDataItem->font();
        font.setBold(true);
        font.setPointSize(12);
        noDataItem->setFont(font);
        
        // Span all columns
        ui->tableWidget->setItem(0, 0, noDataItem);
        ui->tableWidget->setSpan(0, 0, 1, ui->tableWidget->columnCount());
        
        return;
    }
    
    // Calculate starting row number based on current page and page size
    int pageSize = ui->pageSize->currentText().toInt();
    int startingRowNumber = (currentPage - 1) * pageSize;
    
    // Populate the table with call details
    for (int i = 0; i < callList.size(); i++) {
        QJsonObject call = callList[i].toObject();
        
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        
        // Play button - Use the correct key "CallRef-ID"
        QPushButton *playButton = new QPushButton("Play", ui->tableWidget);
        playButton->setProperty("callRefId", call["CallRef-ID"].toString());
        playButton->setProperty("wavPass", call["Wav-Pass"].toString());
        connect(playButton, &QPushButton::clicked, this, [this, playButton]() {
            QString callRefId = playButton->property("callRefId").toString();
            QString wavPass = playButton->property("wavPass").toString();
            apiHandler->streamWaveFile(sessionToken, callRefId, wavPass);
        });
        ui->tableWidget->setCellWidget(row, 0, playButton);
        
        // Set other columns
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(call["Channel"].toString()));
        
        // Determine which ID to display
        QString displayId;
        if (call.contains("Called-ID") && !call["Called-ID"].toString().isEmpty()) {
            displayId = call["Called-ID"].toString();
        } else if (call.contains("Caller-ID") && !call["Caller-ID"].toString().isEmpty()) {
            displayId = call["Caller-ID"].toString();
        } else {
            displayId = call["CallRef-ID"].toString();
        }
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(displayId)); // Display ID
        
        // Call Type (I/O to Incoming/Outgoing)
        QString callType = call["Call-Type"].toString();
        if (callType == "I") {
            callType = "Incoming";
        } else if (callType == "O") {
            callType = "Outgoing";
        }
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(callType));
        
        // Call Status
        QString callStatus = call["Call-Status"].toString();
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(callStatus));
        
        // Format call time
        QString callTimeStr = call["Call-Time"].toString();
        QDateTime callTime = QDateTime::fromString(callTimeStr, "yyyyMMddhhmmss");
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(callTime.toString("yyyy-MM-dd hh:mm:ss")));
        
        // Duration - Use Connect-Duration for the duration column
        QString duration = call["Connect-Duration"].toString();
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(duration));
        
        // Ring Duration
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(call["Ring-Duration"].toString()));
        
        // Connect Duration
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(call["Connect-Duration"].toString()));
        
        // Compression
        ui->tableWidget->setItem(row, 9, new QTableWidgetItem(call["Compression"].toString()));
        
        // Channel Hardware
        ui->tableWidget->setItem(row, 10, new QTableWidgetItem(call["Channel-Hardware"].toString()));
        
        // Set alignment for all items in this row
        for (int col = 1; col < ui->tableWidget->columnCount(); col++) {
            if (ui->tableWidget->item(row, col)) {
                ui->tableWidget->item(row, col)->setTextAlignment(Qt::AlignCenter);
            }
        }
        
        // Set row number in the vertical header
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(startingRowNumber + i + 1)));
    }
    
    // Resize columns to fit content
    ui->tableWidget->resizeColumnsToContents();
    
    // Set horizontal header properties for better alignment
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    
    // Set specific column widths if needed
    ui->tableWidget->setColumnWidth(0, 80);  // Play button
    ui->tableWidget->setColumnWidth(1, 80);  // Channel
    ui->tableWidget->setColumnWidth(2, 150); // Call Ref ID
    ui->tableWidget->setColumnWidth(3, 100); // Call Type
    ui->tableWidget->setColumnWidth(4, 100); // Call Status
    ui->tableWidget->setColumnWidth(5, 180); // Call Time
    ui->tableWidget->setColumnWidth(6, 80);  // Duration
    
    // Add alternating row colors for better readability
    ui->tableWidget->setAlternatingRowColors(true);
    
    // Make sure vertical header (row numbers) is visible
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(30); // Set row height
}

void TimeTimeCalls::handleTableCellClicked(int row, int column)
{
    // This can be removed or left empty since we're handling clicks through the button
}

void TimeTimeCalls::handleWaveFile(const QByteArray &waveData)
{
    qDebug() << "Received wave data, size:" << waveData.size();

    // Create a temporary file to store the wave data
    if (tempWaveFile) {
        delete tempWaveFile;
    }
    tempWaveFile = new QTemporaryFile(this);
    tempWaveFile->setFileTemplate(QDir::tempPath() + "/voicelogger_XXXXXX.wav");
    
    if (!tempWaveFile->open()) {
        QMessageBox::warning(this, "Error", "Could not create temporary file for playback");
        return;
    }

    // Write the wave data to the temporary file
    tempWaveFile->write(waveData);
    tempWaveFile->flush();
    tempWaveFile->seek(0);

    qDebug() << "Created temporary file:" << tempWaveFile->fileName();

    // Create and show the audio player dialog
    AudioPlayerDialog *playerDialog = new AudioPlayerDialog(this);
    playerDialog->setTitle("Call Recording");
    playerDialog->setAudioSource(tempWaveFile->fileName());
    playerDialog->exec();

    delete playerDialog;
}

void TimeTimeCalls::handleWaveFileFailed(const QString &message)
{
    QMessageBox::warning(this, "Error", "Failed to fetch wave file: " + message);
}

void TimeTimeCalls::performSearch()
{
    // Check if the user has any assigned channels
    if (ui->channelGroupCombo->currentText() == "No assigned channels") {
        // Display "No available data" message
        ui->tableWidget->setRowCount(1);
        QTableWidgetItem* noDataItem = new QTableWidgetItem("No assigned channels");
        noDataItem->setTextAlignment(Qt::AlignCenter);
        
        // Create a font for the message
        QFont font = noDataItem->font();
        font.setBold(true);
        font.setPointSize(12);
        noDataItem->setFont(font);
        
        // Span all columns
        ui->tableWidget->setItem(0, 0, noDataItem);
        ui->tableWidget->setSpan(0, 0, 1, ui->tableWidget->columnCount());
        
        // Update total calls count
        ui->labelTotalCalls->setText("Total Connected Calls: 0");
        
        // Update pagination controls
        updatePaginationControls(0);
        
        return;
    }

    // Determine the call type filter
    QString callType;
    switch(ui->callTypeCombo->currentIndex()) {
        case 1: callType = "I"; break; // Incoming
        case 2: callType = "O"; break; // Outgoing
        default: callType = ""; break; // All
    }

    try {
        // Use a large page size to retrieve all data at once
        // This approach works well for reasonably sized datasets
        const int largePageSize = 10000; // Adjust as needed for your application
        
        apiHandler->fetchCallList(
            sessionToken,
            ui->fromDateTime->dateTime(),
            ui->toDateTime->dateTime(),
            ui->phoneNumber->text(),
            callType,
            0, // Always start from the first page
            largePageSize // Request a large number of records
        );
    } catch (const std::exception& e) {
        qDebug() << "Exception in performSearch: " << e.what();
        QMessageBox::warning(this, "Error", "An error occurred while searching: " + QString(e.what()));
    }
}

void TimeTimeCalls::updatePaginationControls(int totalCalls)
{
    // Get current page size (from combo box)
    int pageSize = 50; // Default
    bool ok = false;
    QString pageSizeText = ui->pageSize->currentText();
    
    if (!pageSizeText.isEmpty()) {
        int size = pageSizeText.toInt(&ok);
        if (ok && size > 0) {
            pageSize = size;
        } else {
            ui->pageSize->setCurrentText("50");
        }
    } else {
        ui->pageSize->setCurrentText("50");
    }
    
    // Calculate total pages (minimum 1 page)
    totalPages = qMax(1, (totalCalls + pageSize - 1) / pageSize);
    
    // Get current page from text field
    bool conversionOk = false;
    int currentPageValue = ui->currentPage->text().toInt(&conversionOk);
    
    // Ensure current page is valid
    if (!conversionOk || currentPageValue < 1) {
        currentPageValue = 1;
        ui->currentPage->setText("1");
    } else if (currentPageValue > totalPages) {
        currentPageValue = totalPages;
        ui->currentPage->setText(QString::number(totalPages));
    }
    
    // Update button states
    ui->btnPrevPage->setEnabled(currentPageValue > 1);
    ui->btnNextPage->setEnabled(currentPageValue < totalPages);
}

void TimeTimeCalls::on_btnPrevPage_clicked()
{
    bool conversionOk = false;
    int currentPageValue = ui->currentPage->text().toInt(&conversionOk);
    
    if (conversionOk && currentPageValue > 1) {
        ui->currentPage->setText(QString::number(currentPageValue - 1));
        // Handle page change
        QJsonArray callList = lastCallDetails["List"].toArray();
        filterCallsByChannelGroup(callList);
        applyClientSidePagination(callList);
    }
}

void TimeTimeCalls::on_btnNextPage_clicked()
{
    bool conversionOk = false;
    int currentPageValue = ui->currentPage->text().toInt(&conversionOk);
    
    if (conversionOk && currentPageValue < totalPages) {
        ui->currentPage->setText(QString::number(currentPageValue + 1));
        // Handle page change
        QJsonArray callList = lastCallDetails["List"].toArray();
        filterCallsByChannelGroup(callList);
        applyClientSidePagination(callList);
    }
}

void TimeTimeCalls::onChannelGroupChanged(int index)
{
    // If we have stored call details, apply filtering and pagination
    if (!lastCallDetails.isEmpty()) {
        // Reset to page 1 when changing channel groups
        ui->currentPage->setText("1");
        
        QJsonArray callList = lastCallDetails["List"].toArray();
        filterCallsByChannelGroup(callList);
        applyClientSidePagination(callList);
    }
}

bool TimeTimeCalls::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        if (obj == ui->fromDateTime) {
            showFromDateCalendar();
            return true;
        } else if (obj == ui->toDateTime) {
            showToDateCalendar();
            return true;
        } else if (obj == ui->phoneNumber) {
            // When phone number field is clicked, show all suggestions
            if (phoneCompleter && phoneNumbersModel) {
                // Clear the current text to show all suggestions
                bool hadText = !ui->phoneNumber->text().isEmpty();
                QString savedText = ui->phoneNumber->text();
                
                // Temporarily clear the text to show all options
                ui->phoneNumber->clear();
                
                // Show the completer popup with all suggestions
                phoneCompleter->complete();
                
                // If there was text, restore it
                if (hadText) {
                    QTimer::singleShot(10, this, [this, savedText]() {
                        ui->phoneNumber->setText(savedText);
                        // Re-show the completer with the filter applied
                        phoneCompleter->complete();
                    });
                }
                
                return true;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void TimeTimeCalls::showFromDateCalendar()
{
    QDateTime currentDate = ui->fromDateTime->dateTime();
    fromDateCalendar->setSelectedDate(currentDate.date());
    
    // Position the calendar under the date edit widget
    QPoint pos = ui->fromDateTime->mapToGlobal(ui->fromDateTime->rect().bottomLeft());
    fromDateCalendar->move(pos);
    fromDateCalendar->show();
}

void TimeTimeCalls::showToDateCalendar()
{
    QDateTime currentDate = ui->toDateTime->dateTime();
    toDateCalendar->setSelectedDate(currentDate.date());
    
    // Position the calendar under the date edit widget
    QPoint pos = ui->toDateTime->mapToGlobal(ui->toDateTime->rect().bottomLeft());
    toDateCalendar->move(pos);
    toDateCalendar->show();
}

void TimeTimeCalls::onFromDateSelected()
{
    // Get the selected date from the calendar
    QDate selectedDate = fromDateCalendar->selectedDate();
    
    // Preserve the time part from the existing date time
    QTime time = ui->fromDateTime->time();
    
    // Set the new date time
    QDateTime newDateTime(selectedDate, time);
    ui->fromDateTime->setDateTime(newDateTime);
    
    // Hide the calendar
    fromDateCalendar->hide();
    
    // Update phone number suggestions for the new date range
    updatePhoneNumberSuggestions();
}

void TimeTimeCalls::onToDateSelected()
{
    // Get the selected date from the calendar
    QDate selectedDate = toDateCalendar->selectedDate();
    
    // Preserve the time part from the existing date time
    QTime time = ui->toDateTime->time();
    
    // Set the new date time
    QDateTime newDateTime(selectedDate, time);
    ui->toDateTime->setDateTime(newDateTime);
    
    // Hide the calendar
    toDateCalendar->hide();
    
    // Update phone number suggestions for the new date range
    updatePhoneNumberSuggestions();
}

void TimeTimeCalls::applyClientSidePagination(const QJsonArray &filteredList)
{
    // Debug output
    qDebug() << "Applying pagination with page size:" << ui->pageSize->currentText();
    qDebug() << "Current page:" << ui->currentPage->text();
    
    // Clear the table
    ui->tableWidget->setRowCount(0);
    
    // Update total calls count
    int totalFilteredCalls = filteredList.size();
    ui->labelTotalCalls->setText("Total Connected Calls: " + QString::number(totalFilteredCalls));
    
    // Update pagination controls with the filtered count
    updatePaginationControls(totalFilteredCalls);
    
    // Get current page number from input field
    bool conversionOk = false;
    int currentPageValue = ui->currentPage->text().toInt(&conversionOk);
    if (!conversionOk || currentPageValue < 1) {
        currentPageValue = 1;
        ui->currentPage->setText("1");
    }
    
    // Get page size from combo box
    int pageSize = 50; // Default
    QString pageSizeText = ui->pageSize->currentText();
    
    if (!pageSizeText.isEmpty()) {
        int size = pageSizeText.toInt(&conversionOk);
        if (conversionOk && size > 0) {
            pageSize = size;
        } else {
            ui->pageSize->setCurrentText("50");
        }
    } else {
        ui->pageSize->setCurrentText("50");
    }
    
    // Update the currentPage member variable to keep track of current page
    currentPage = currentPageValue;
    
    // Calculate start and end indices for the current page
    int startIndex = (currentPage - 1) * pageSize;
    int endIndex = qMin(startIndex + pageSize, totalFilteredCalls);
    
    // Debug output
    qDebug() << "Using page size:" << pageSize << "for range" << startIndex << "to" << endIndex 
             << "of" << totalFilteredCalls << "records";
             
    // Check if we have any data
    if (filteredList.isEmpty()) {
        // Display "No available data" message
        ui->tableWidget->setRowCount(1);
        QTableWidgetItem* noDataItem = new QTableWidgetItem("No available data");
        noDataItem->setTextAlignment(Qt::AlignCenter);
        
        // Create a font for the message
        QFont font = noDataItem->font();
        font.setBold(true);
        font.setPointSize(12);
        noDataItem->setFont(font);
        
        // Span all columns
        ui->tableWidget->setItem(0, 0, noDataItem);
        ui->tableWidget->setSpan(0, 0, 1, ui->tableWidget->columnCount());
        
        return;
    }
    
    // Check if current page is now invalid (could happen after filtering)
    if (startIndex >= totalFilteredCalls && totalFilteredCalls > 0) {
        // Adjust to the last valid page
        currentPageValue = qMax(1, (totalFilteredCalls + pageSize - 1) / pageSize);
        ui->currentPage->setText(QString::number(currentPageValue));
        
        // Recalculate the indices
        startIndex = (currentPageValue - 1) * pageSize;
        endIndex = qMin(startIndex + pageSize, totalFilteredCalls);
    }
    
    // Populate the table with the paginated subset of filtered call details
    for (int i = startIndex; i < endIndex; i++) {
        QJsonObject call = filteredList[i].toObject();
        
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        
        // Play button - Use the correct key "CallRef-ID"
        QPushButton *playButton = new QPushButton("Play", ui->tableWidget);
        playButton->setProperty("callRefId", call["CallRef-ID"].toString());
        playButton->setProperty("wavPass", call["Wav-Pass"].toString());
        connect(playButton, &QPushButton::clicked, this, [this, playButton]() {
            QString callRefId = playButton->property("callRefId").toString();
            QString wavPass = playButton->property("wavPass").toString();
            apiHandler->streamWaveFile(sessionToken, callRefId, wavPass);
        });
        ui->tableWidget->setCellWidget(row, 0, playButton);
        
        // Set other columns (same as in updateCallDetailsTable)
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(call["Channel"].toString()));
        
        // Determine which ID to display
        QString displayId;
        if (call.contains("Called-ID") && !call["Called-ID"].toString().isEmpty()) {
            displayId = call["Called-ID"].toString();
        } else if (call.contains("Caller-ID") && !call["Caller-ID"].toString().isEmpty()) {
            displayId = call["Caller-ID"].toString();
        } else {
            displayId = call["CallRef-ID"].toString();
        }
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(displayId)); // Display ID
        
        // Call Type (I/O to Incoming/Outgoing)
        QString callType = call["Call-Type"].toString();
        if (callType == "I") {
            callType = "Incoming";
        } else if (callType == "O") {
            callType = "Outgoing";
        }
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(callType));
        
        // Call Status
        QString callStatus = call["Call-Status"].toString();
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(callStatus));
        
        // Format call time
        QString callTimeStr = call["Call-Time"].toString();
        QDateTime callTime = QDateTime::fromString(callTimeStr, "yyyyMMddhhmmss");
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(callTime.toString("yyyy-MM-dd hh:mm:ss")));
        
        // Duration - Use Connect-Duration for the duration column
        QString duration = call["Connect-Duration"].toString();
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(duration));
        
        // Ring Duration
        ui->tableWidget->setItem(row, 7, new QTableWidgetItem(call["Ring-Duration"].toString()));
        
        // Connect Duration
        ui->tableWidget->setItem(row, 8, new QTableWidgetItem(call["Connect-Duration"].toString()));
        
        // Compression
        ui->tableWidget->setItem(row, 9, new QTableWidgetItem(call["Compression"].toString()));
        
        // Channel Hardware
        ui->tableWidget->setItem(row, 10, new QTableWidgetItem(call["Channel-Hardware"].toString()));
        
        // Set alignment for all items in this row
        for (int col = 1; col < ui->tableWidget->columnCount(); col++) {
            if (ui->tableWidget->item(row, col)) {
                ui->tableWidget->item(row, col)->setTextAlignment(Qt::AlignCenter);
            }
        }
        
        // Set row number in the vertical header
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(i + 1)));
    }
    
    // Resize columns to fit content
    ui->tableWidget->resizeColumnsToContents();
    
    // Set horizontal header properties for better alignment
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    
    // Set specific column widths if needed
    ui->tableWidget->setColumnWidth(0, 80);  // Play button
    ui->tableWidget->setColumnWidth(1, 80);  // Channel
    ui->tableWidget->setColumnWidth(2, 150); // Call Ref ID
    ui->tableWidget->setColumnWidth(3, 100); // Call Type
    ui->tableWidget->setColumnWidth(4, 100); // Call Status
    ui->tableWidget->setColumnWidth(5, 180); // Call Time
    ui->tableWidget->setColumnWidth(6, 80);  // Duration
    
    // Add alternating row colors for better readability
    ui->tableWidget->setAlternatingRowColors(true);
    
    // Make sure vertical header (row numbers) is visible
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(30); // Set row height
}

void TimeTimeCalls::setupPhoneNumberAutocomplete()
{
    // Create a completer for the phone number field
    phoneCompleter = new QCompleter(phoneNumbersModel, this);
    phoneCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    phoneCompleter->setFilterMode(Qt::MatchContains); // Show matches that contain the typed text
    phoneCompleter->setCompletionMode(QCompleter::PopupCompletion); // Show popup on user request
    
    // Set the completer for the phone number field
    ui->phoneNumber->setCompleter(phoneCompleter);
    
    // Install event filter to show all suggestions when clicked
    ui->phoneNumber->installEventFilter(this);
    
    // Initially populate the phone number suggestions
    updatePhoneNumberSuggestions();
}

void TimeTimeCalls::updatePhoneNumberSuggestions()
{
    // Don't try to update if no session token
    if (sessionToken.isEmpty()) {
        return;
    }
    
    // Show a loading indicator in the completer model
    QStringList loadingList = {"Loading phone numbers..."};
    phoneNumbersModel->setStringList(loadingList);
    
    // Fetch data from API using current date range
    apiHandler->fetchCallList(
        sessionToken,
        ui->fromDateTime->dateTime(),
        ui->toDateTime->dateTime(),
        "", // No phone filter
        "", // No call type filter
        0,  // Page 0
        1000 // Get up to 1000 records
    );
    
    // Create a one-time connection to process the results
    QMetaObject::Connection* connection = new QMetaObject::Connection;
    *connection = connect(apiHandler, &APIHandler::callDetailsReceived, this, 
        [this, connection](const QJsonObject &details) {
            // Disconnect after receiving the response
            QObject::disconnect(*connection);
            delete connection;
            
            // Create a set to store unique phone numbers
            QSet<QString> uniqueNumbers;
            
            // Process the response
            if (details.contains("List") && details["List"].isArray()) {
                QJsonArray callList = details["List"].toArray();
                
                // Extract phone numbers from calls
                for (int i = 0; i < callList.size(); i++) {
                    QJsonObject call = callList[i].toObject();
                    
                    // Get both caller and called IDs
                    if (call.contains("Called-ID") && !call["Called-ID"].toString().isEmpty()) {
                        uniqueNumbers.insert(call["Called-ID"].toString());
                    }
                    
                    if (call.contains("Caller-ID") && !call["Caller-ID"].toString().isEmpty()) {
                        uniqueNumbers.insert(call["Caller-ID"].toString());
                    }
                }
            }
            
            // Convert set to sorted list for better user experience
            QStringList phoneList = uniqueNumbers.values();
            std::sort(phoneList.begin(), phoneList.end());
            
            // Update the model with new phone numbers
            phoneNumbersModel->setStringList(phoneList);
            
            // Debug output
            qDebug() << "Updated phone number suggestions with" << uniqueNumbers.count() << "unique numbers";
        });
}

