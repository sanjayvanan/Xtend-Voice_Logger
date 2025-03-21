#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include "apihandler.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include "mainwindow.h"
#include "usermanagement.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
    , apiHandler(new APIHandler(this))
{
    ui->setupUi(this);
    setWindowTitle("Zosh Voice Logger - Login");

    // Set the login window to full screen
    this->setWindowState(Qt::WindowMaximized); // or use Qt::WindowFullScreen

    // Get backend token using admin credentials
    apiHandler->login("admin", APIHandler::hashPassword("admin"));
    connect(apiHandler, &APIHandler::loginSuccessful, 
            [this](const QString &token) {
                backendToken = token;
            });
            
    // Initialize the database
    initializeDatabase();
}

login::~login()
{
    delete ui;
}

void login::initializeDatabase()
{
    // Create database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("voicelogger.db");
    
    if (!db.open()) {
        qDebug() << "Error: Failed to connect to database";
        return;
    }
    
    createTablesIfNotExist();
    // addDefaultUserIfNotExist();
}

void login::createTablesIfNotExist()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
              "username TEXT UNIQUE NOT NULL,"
              "password_hash TEXT NOT NULL,"
              "role TEXT NOT NULL)");  // 'admin' or 'user'
              
    // Create channel_groups table
    query.exec("CREATE TABLE IF NOT EXISTS channel_groups ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
              "group_name TEXT NOT NULL,"
              "channels TEXT NOT NULL)");  // Comma-separated list of channel numbers
              
    // Create user_channel_groups table for assignments
    query.exec("CREATE TABLE IF NOT EXISTS user_channel_groups ("
              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
              "username TEXT NOT NULL,"
              "group_name TEXT NOT NULL,"
              "FOREIGN KEY (username) REFERENCES users(username) ON DELETE CASCADE,"
              "FOREIGN KEY (group_name) REFERENCES channel_groups(group_name) ON DELETE CASCADE,"
              "UNIQUE(username, group_name))");
              
    // Add default channel groups if they don't exist
    query.prepare("SELECT COUNT(*) FROM channel_groups");
    if (query.exec() && query.next() && query.value(0).toInt() == 0) {
        // Add default individual channels
        query.exec("INSERT INTO channel_groups (group_name, channels) VALUES ('Channel 1', '1')");
        query.exec("INSERT INTO channel_groups (group_name, channels) VALUES ('Channel 2', '2')");
        query.exec("INSERT INTO channel_groups (group_name, channels) VALUES ('Channel 3', '3')");
        query.exec("INSERT INTO channel_groups (group_name, channels) VALUES ('Channel 4', '4')");
    }

    // Add channels table
    query.exec("CREATE TABLE IF NOT EXISTS channels ("
               "channel_id INTEGER PRIMARY KEY, "
               "channel_name TEXT NOT NULL UNIQUE)");
}

// void login::addDefaultUserIfNotExist()
// {
//     QSqlQuery query;
    
//     // First check if admin user exists
//     query.prepare("SELECT username FROM users WHERE username = 'Sanjayvanan'");
//     if (!query.exec()) {
//         qDebug() << "Error checking admin user:" << query.lastError().text();
//         return;
//     }
    
//     // If admin user doesn't exist, create it
//     if (!query.next()) {
//         query.prepare("INSERT INTO users (username, password_hash, role) "
//                      "VALUES (:username, :password_hash, :role)");
        
//         // Add admin user
//         query.bindValue(":username", "Sanjayvanan");
        
//         // Hash the password 'admin' using SHA256
//         QString hashedPassword = QString(QCryptographicHash::hash("admin",
//                                 QCryptographicHash::Sha256).toHex());
        
//         query.bindValue(":password_hash", hashedPassword);
//         query.bindValue(":role", "admin");
        
//         if (!query.exec()) {
//             qDebug() << "Error creating admin user:" << query.lastError().text();
//         } else {
//             qDebug() << "Admin user created successfully";
//         }
//     }

//     // Now check for the regular user
//     query.prepare("SELECT username FROM users WHERE username = 'RegularUser'");
//     if (!query.exec()) {
//         qDebug() << "Error checking regular user:" << query.lastError().text();
//         return;
//     }
    
//     // If regular user doesn't exist, create it
//     if (!query.next()) {
//         query.prepare("INSERT INTO users (username, password_hash, role) "
//                      "VALUES (:username, :password_hash, :role)");
        
//         // Add regular user
//         query.bindValue(":username", "RegularUser");
        
//         // Hash the password 'userpassword' using SHA256
//         QString hashedPassword = QString(QCryptographicHash::hash("userpassword",
//                                QCryptographicHash::Sha256).toHex());
        
//         query.bindValue(":password_hash", hashedPassword);
//         query.bindValue(":role", "user");
        
//         if (!query.exec()) {
//             qDebug() << "Error creating regular user:" << query.lastError().text();
//         } else {
//             qDebug() << "Regular user created successfully";
//         }
//     }
// }

bool login::validateCredentials(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT password_hash, role FROM users WHERE username = :username");
    query.bindValue(":username", username);
    
    if (query.exec() && query.next()) {
        QString storedHash = query.value(0).toString();
        QString role = query.value(1).toString();
        
        // Hash the input password using SHA256 to match stored hash
        QString inputHash = QString(QCryptographicHash::hash(password.toUtf8(), 
                           QCryptographicHash::Sha256).toHex());
        
        if (storedHash == inputHash) {
            currentRole = role;
            return true;
        }
    }
    return false;
}

void login::on_login_2_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit__password->text();

    ui->login_2->setEnabled(false);

    if (validateCredentials(username, password)) {
        // Use the already obtained backend token
        handleLoginSuccess(backendToken);
        this->hide(); // Hide the login window after successful login
    } else {
        handleLoginFailure("Invalid username or password");
    }
}

void login::handleLoginSuccess(const QString &token)
{
    QString username = ui->lineEdit_username->text();
    
    // Query the database to get the user's role
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE username = :username");
    query.bindValue(":username", username);
    
    if (query.exec() && query.next()) {
        QString role = query.value(0).toString();
        emit loginSuccessful(token, username, role);
    }
}

void login::handleLoginFailure(const QString &message)
{
    ui->login_2->setEnabled(true);
    QMessageBox::warning(this, "Login", "Login failed: " + message);
}
