#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidgetItem>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTemporaryFile>
#include <QDir>
#include <QPushButton>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QFormLayout>
#include <QTableWidget>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , apiHandler(new APIHandler(this))
    , dashboard(new Dashboard(this))
    , liveCalls(new LiveCalls(this))
    , timeTimeCalls(new TimeTimeCalls(this))
    , userManagement(nullptr)  // Initialize to nullptr
{
    ui->setupUi(this);
    setWindowTitle("Zosh Voice Logger");

    // Initialize widgets
    dashboard = new Dashboard(this);
    timeTimeCalls = new TimeTimeCalls(this);
    liveCalls = new LiveCalls(this);

    // Remove existing widgets from stacked widget
    while (ui->stackedWidget->count() > 0) {
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    }

    // Add widgets to stacked widget in the correct order
    ui->stackedWidget->addWidget(dashboard);     // Index 0: Dashboard
    ui->stackedWidget->addWidget(liveCalls);     // Index 1: Live Calls
    ui->stackedWidget->addWidget(timeTimeCalls); // Index 2: Time to Time Calls

    // Connect button clicks to switch pages
    connect(ui->btnDashboard, &QPushButton::clicked, this, &MainWindow::on_btnDashboard_clicked);
    connect(ui->btnLiveCalls, &QPushButton::clicked, this, &MainWindow::on_btnLiveCalls_clicked);
    connect(ui->btnTimeTime, &QPushButton::clicked, this, &MainWindow::on_btnTimeTimeCalls_clicked);

    // Connect logout button
    connect(ui->btnLogout, &QPushButton::clicked, this, &MainWindow::on_actionLogout_triggered);

    // Set default view
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSessionToken(const QString &token, const QString &username, const QString &role)
{
    sessionToken = token;
    currentUserRole = role;
    
    // Update UI with username
    ui->labelUserName->setText(username);
    
    // Initialize dashboard first
    if (dashboard) {
        dashboard->setSessionToken(token);
        dashboard->stopMonitoring(); // Stop any existing monitoring
        dashboard->startMonitoring(); // Start fresh monitoring
    }
    
    // Initialize time to time calls
    if (timeTimeCalls) {
        timeTimeCalls->setSessionToken(token);
    }
    
    // Initialize live calls
    if (liveCalls) {
        liveCalls->setSessionToken(token);
        liveCalls->stopMonitoring(); // Ensure monitoring is stopped initially
    }
    
    // Show/hide admin features based on role
    if (role == "admin") {
        // Hide the user management button initially
        if (ui->btnUserManagement) {
            ui->btnUserManagement->hide();
        }
        
        // Delay user management setup and button display
        QTimer::singleShot(1000, this, [this]() {
            try {
                setupUserManagement();
                if (ui->btnUserManagement) {
                    ui->btnUserManagement->show();
                }
            } catch (const std::exception& e) {
                qDebug() << "Error setting up user management:" << e.what();
                QMessageBox::warning(this, "Warning", 
                    "Error initializing admin features. Some functions may be limited.");
            }
        });
    } else {
        if (ui->btnUserManagement) {
            ui->btnUserManagement->hide();
        }
        if (userManagementWidget && userManagementWidget->isVisible()) {
            userManagementWidget->hide();
        }
    }
    
    // Ensure we're showing the dashboard
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionLogout_triggered()
{
    if (!sessionToken.isEmpty()) {
        apiHandler->logout(sessionToken);
        handleLogoutSuccess();
    }
}

void MainWindow::handleLogoutSuccess()
{
    // Create and show new login window
    login *loginWindow = new login();
    connect(loginWindow, &login::loginSuccessful,
            [this](const QString &token, const QString &username, const QString &role) {
        setSessionToken(token, username, role);
        show();
    });
    loginWindow->show();
    
    // Hide main window
    hide();
}

void MainWindow::handleLogoutFailure(const QString &message)
{
    QMessageBox::warning(this, "Logout", "Logout failed: " + message);
}

void MainWindow::setupUserManagement()
{
    if (userManagementWidget) {
        delete userManagementWidget;
        userManagementWidget = nullptr;
        tableUsers = nullptr;
    }

    userManagementWidget = new QWidget(nullptr); // Create as a separate window
    userManagementWidget->setAttribute(Qt::WA_DeleteOnClose);
    userManagementWidget->setWindowTitle("User Management");
    
    QVBoxLayout *layout = new QVBoxLayout(userManagementWidget);

    // Add User Form Group
    QGroupBox *addUserGroup = new QGroupBox("Add New User", userManagementWidget);
    QFormLayout *formLayout = new QFormLayout(addUserGroup);

    // Create form fields
    QLineEdit *usernameEdit = new QLineEdit(addUserGroup);
    QLineEdit *passwordEdit = new QLineEdit(addUserGroup);
    passwordEdit->setEchoMode(QLineEdit::Password);
    QComboBox *roleCombo = new QComboBox(addUserGroup);
    roleCombo->addItems({"user", "admin"});

    formLayout->addRow("Username:", usernameEdit);
    formLayout->addRow("Password:", passwordEdit);
    formLayout->addRow("Role:", roleCombo);

    QPushButton *addButton = new QPushButton("Add User", addUserGroup);
    formLayout->addRow(addButton);

    // Setup Users Table
    tableUsers = new QTableWidget(userManagementWidget);
    tableUsers->setColumnCount(3);
    tableUsers->setHorizontalHeaderLabels({"Username", "Role", "Actions"});
    tableUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    tableUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableUsers->horizontalHeader()->setStretchLastSection(true);

    // Add Delete Button
    QPushButton *deleteButton = new QPushButton("Delete Selected User", userManagementWidget);

    // Add widgets to layout
    layout->addWidget(addUserGroup);
    layout->addWidget(tableUsers);
    layout->addWidget(deleteButton);

    // Connect signals
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddUserClicked);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteUserClicked);

    // Set window properties
    userManagementWidget->setMinimumSize(400, 500);
    userManagementWidget->resize(500, 600);

    // Initial refresh of user list
    refreshUserList();
}

void MainWindow::refreshUserList()
{
    if (!tableUsers) return;

    tableUsers->setRowCount(0);
    
    QSqlQuery query("SELECT username, role FROM users");
    if (!query.exec()) {
        qDebug() << "Error fetching users:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int row = tableUsers->rowCount();
        tableUsers->insertRow(row);
        tableUsers->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        tableUsers->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
    }
}

void MainWindow::onAddUserClicked()
{
    if (!userManagementWidget) return;

    QLineEdit *usernameEdit = userManagementWidget->findChild<QLineEdit*>();
    QLineEdit *passwordEdit = userManagementWidget->findChildren<QLineEdit*>()[1];
    QComboBox *roleCombo = userManagementWidget->findChild<QComboBox*>();

    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString role = roleCombo->currentText();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username and password are required");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash, role) "
                 "VALUES (:username, :password_hash, :role)");
    query.bindValue(":username", username);
    query.bindValue(":password_hash", 
                   QString(QCryptographicHash::hash(password.toUtf8(), 
                   QCryptographicHash::Sha256).toHex()));
    query.bindValue(":role", role);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "User added successfully");
        refreshUserList();
        
        // Clear the form
        usernameEdit->clear();
        passwordEdit->clear();
        roleCombo->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Error", "Failed to add user: " + query.lastError().text());
    }
}

void MainWindow::onDeleteUserClicked()
{
    // Get the selected row
    int currentRow = tableUsers->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Error", "Please select a user to delete");
        return;
    }

    // Get the username from the selected row
    QString username = tableUsers->item(currentRow, 0)->text();

    // Confirm deletion
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete",
        "Are you sure you want to delete user '" + username + "'?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Create a query to delete the user
        QSqlQuery query;
        query.prepare("DELETE FROM users WHERE username = ?");
        query.addBindValue(username);

        if (query.exec()) {
            // Remove the row from the table
            tableUsers->removeRow(currentRow);
            QMessageBox::information(this, "Success", "User deleted successfully");
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete user: " + query.lastError().text());
        }
    }
}

void MainWindow::on_btnDashboard_clicked()
{
    ui->stackedWidget->setCurrentWidget(dashboard);
}

void MainWindow::on_btnLiveCalls_clicked()
{
    ui->stackedWidget->setCurrentWidget(liveCalls);
}

void MainWindow::on_btnTimeTimeCalls_clicked()
{
    ui->stackedWidget->setCurrentWidget(timeTimeCalls);
}

void MainWindow::on_btnUserManagement_clicked()
{
    if (!userManagement) {
        userManagement = new UserManagement(this);
        userManagement->setAttribute(Qt::WA_DeleteOnClose);
        connect(userManagement, &QWidget::destroyed, [this]() {
            userManagement = nullptr;
        });
    }
    
    if (userManagement) {
        userManagement->setSessionToken(sessionToken);
        userManagement->show();
        userManagement->raise();
        userManagement->activateWindow();
        userManagement->refreshUserList(); // Refresh the user list when shown
    }
}

