#include "usermanagement.h"
#include "ui_usermanagement.h"
#include <QCryptographicHash>
#include <QSqlError>
#include <QDebug>

UserManagement::UserManagement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserManagement)
{
    ui->setupUi(this);
    
    // Get references to UI elements
    userTable = ui->userTable;
    usernameEdit = ui->usernameEdit;
    passwordEdit = ui->passwordEdit;
    roleCombo = ui->roleCombo;
    addButton = ui->addButton;
    editButton = ui->editButton;
    deleteButton = ui->deleteButton;
    clearButton = ui->clearButton;
    
    // Set up table
    userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    // Set up initial button states
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);
    
    // Connect signals
    connect(addButton, &QPushButton::clicked, this, &UserManagement::onAddUserClicked);
    connect(editButton, &QPushButton::clicked, this, &UserManagement::onEditUserClicked);
    connect(deleteButton, &QPushButton::clicked, this, &UserManagement::onDeleteUserClicked);
    connect(clearButton, &QPushButton::clicked, this, &UserManagement::clearForm);
    connect(userTable, &QTableWidget::cellClicked, this, &UserManagement::onTableItemClicked);
    
    // Initial refresh
    refreshUserList();
}

UserManagement::~UserManagement()
{
    delete ui;
}

void UserManagement::setupUI()
{
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel *titleLabel = new QLabel("User Management", this);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Form group box
    QGroupBox *formGroup = new QGroupBox("User Details", this);
    QFormLayout *formLayout = new QFormLayout(formGroup);

    // Form fields
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    roleCombo = new QComboBox(this);
    roleCombo->addItems({"user", "admin"});

    formLayout->addRow("Username:", usernameEdit);
    formLayout->addRow("Password:", passwordEdit);
    formLayout->addRow("Role:", roleCombo);

    mainLayout->addWidget(formGroup);

    // Buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add User", this);
    editButton = new QPushButton("Update User", this);
    deleteButton = new QPushButton("Delete User", this);
    clearButton = new QPushButton("Clear Form", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(clearButton);
    mainLayout->addLayout(buttonLayout);

    // Table
    userTable = new QTableWidget(this);
    userTable->setColumnCount(3);
    userTable->setHorizontalHeaderLabels({"Username", "Role", "Actions"});
    userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    userTable->setSelectionMode(QAbstractItemView::SingleSelection);
    userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(userTable);

    // Initial button states
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);

    setMinimumSize(600, 400);
}

void UserManagement::setupConnections()
{
    connect(addButton, &QPushButton::clicked, this, &UserManagement::onAddUserClicked);
    connect(editButton, &QPushButton::clicked, this, &UserManagement::onEditUserClicked);
    connect(deleteButton, &QPushButton::clicked, this, &UserManagement::onDeleteUserClicked);
    connect(clearButton, &QPushButton::clicked, this, &UserManagement::clearForm);
    connect(userTable, &QTableWidget::cellClicked, this, &UserManagement::onTableItemClicked);
}

void UserManagement::refreshUserList()
{
    userTable->setRowCount(0);
    QSqlQuery query("SELECT username, role FROM users");
    
    if (!query.exec()) {
        QMessageBox::warning(this, "Error", "Failed to fetch users: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        int row = userTable->rowCount();
        userTable->insertRow(row);
        userTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        userTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
    }
}

void UserManagement::onAddUserClicked()
{
    if (!validateInput()) {
        return;
    }

    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString role = roleCombo->currentText();

    // Check if username already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT username FROM users WHERE username = ?");
    checkQuery.addBindValue(username);
    
    if (checkQuery.exec() && checkQuery.next()) {
        QMessageBox::warning(this, "Error", "Username already exists!");
        return;
    }

    // Add new user
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash, role) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(QString(QCryptographicHash::hash(password.toUtf8(), 
                      QCryptographicHash::Sha256).toHex()));
    query.addBindValue(role);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "User added successfully!");
        clearForm();
        refreshUserList();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add user: " + query.lastError().text());
    }
}

void UserManagement::onEditUserClicked()
{
    if (currentEditingRow < 0 || !validateInput()) {
        return;
    }

    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString role = roleCombo->currentText();
    QString currentUsername = userTable->item(currentEditingRow, 0)->text();

    QSqlQuery query;
    if (password.isEmpty()) {
        // Update without changing password
        query.prepare("UPDATE users SET username = ?, role = ? WHERE username = ?");
        query.addBindValue(username);
        query.addBindValue(role);
        query.addBindValue(currentUsername);
    } else {
        // Update including new password
        query.prepare("UPDATE users SET username = ?, password_hash = ?, role = ? WHERE username = ?");
        query.addBindValue(username);
        query.addBindValue(QString(QCryptographicHash::hash(password.toUtf8(), 
                         QCryptographicHash::Sha256).toHex()));
        query.addBindValue(role);
        query.addBindValue(currentUsername);
    }

    if (query.exec()) {
        QMessageBox::information(this, "Success", "User updated successfully!");
        clearForm();
        refreshUserList();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update user: " + query.lastError().text());
    }
}

void UserManagement::onDeleteUserClicked()
{
    if (currentEditingRow < 0) {
        return;
    }

    QString username = userTable->item(currentEditingRow, 0)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete",
        "Are you sure you want to delete user: " + username + "?",
        QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM users WHERE username = ?");
        query.addBindValue(username);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "User deleted successfully!");
            clearForm();
            refreshUserList();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete user: " + query.lastError().text());
        }
    }
}

void UserManagement::onTableItemClicked(int row, int column)
{
    currentEditingRow = row;
    usernameEdit->setText(userTable->item(row, 0)->text());
    roleCombo->setCurrentText(userTable->item(row, 1)->text());
    passwordEdit->clear(); // Don't show password
    
    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
    addButton->setEnabled(false);
}

void UserManagement::clearForm()
{
    usernameEdit->clear();
    passwordEdit->clear();
    roleCombo->setCurrentIndex(0);
    currentEditingRow = -1;
    
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);
    addButton->setEnabled(true);
}

bool UserManagement::validateInput()
{
    if (usernameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Username cannot be empty!");
        return false;
    }

    if (currentEditingRow < 0 && passwordEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Password cannot be empty for new users!");
        return false;
    }

    return true;
}

void UserManagement::setSessionToken(const QString &token)
{
    sessionToken = token;
}
