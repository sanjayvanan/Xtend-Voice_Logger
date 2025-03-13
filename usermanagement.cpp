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
    
    // Get references to UI elements for user management
    userTable = ui->userTable;
    usernameEdit = ui->usernameEdit;
    passwordEdit = ui->passwordEdit;
    roleCombo = ui->roleCombo;
    addButton = ui->addButton;
    editButton = ui->editButton;
    deleteButton = ui->deleteButton;
    clearButton = ui->clearButton;
    
    // Get references to UI elements for channel group management
    channelGroupTable = ui->channelGroupTable;
    groupNameEdit = ui->groupNameEdit;
    channel1Check = ui->channel1Check;
    channel2Check = ui->channel2Check;
    channel3Check = ui->channel3Check;
    channel4Check = ui->channel4Check;
    addChannelGroupButton = ui->addChannelGroupButton;
    editChannelGroupButton = ui->editChannelGroupButton;
    deleteChannelGroupButton = ui->deleteChannelGroupButton;
    clearChannelGroupButton = ui->clearChannelGroupButton;
    
    // Set up tables
    userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    channelGroupTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    // Set up initial button states
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);
    editChannelGroupButton->setEnabled(false);
    deleteChannelGroupButton->setEnabled(false);
    
    // Connect signals for user management
    connect(addButton, &QPushButton::clicked, this, &UserManagement::onAddUserClicked);
    connect(editButton, &QPushButton::clicked, this, &UserManagement::onEditUserClicked);
    connect(deleteButton, &QPushButton::clicked, this, &UserManagement::onDeleteUserClicked);
    connect(clearButton, &QPushButton::clicked, this, &UserManagement::clearForm);
    connect(userTable, &QTableWidget::cellClicked, this, &UserManagement::onTableItemClicked);
    
    // Connect signals for channel group management
    connect(addChannelGroupButton, &QPushButton::clicked, this, &UserManagement::onAddChannelGroupClicked);
    connect(editChannelGroupButton, &QPushButton::clicked, this, &UserManagement::onEditChannelGroupClicked);
    connect(deleteChannelGroupButton, &QPushButton::clicked, this, &UserManagement::onDeleteChannelGroupClicked);
    connect(clearChannelGroupButton, &QPushButton::clicked, this, &UserManagement::clearChannelGroupForm);
    connect(channelGroupTable, &QTableWidget::cellClicked, this, &UserManagement::onChannelGroupTableItemClicked);
    
    // Initial refresh
    refreshUserList();
    refreshChannelGroupList();
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

void UserManagement::refreshChannelGroupList()
{
    channelGroupTable->setRowCount(0);
    QSqlQuery query("SELECT group_name, channels FROM channel_groups");
    
    if (!query.exec()) {
        QMessageBox::warning(this, "Error", "Failed to fetch channel groups: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        int row = channelGroupTable->rowCount();
        channelGroupTable->insertRow(row);
        channelGroupTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        channelGroupTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
    }
}

QList<QPair<QString, QStringList>> UserManagement::getChannelGroups()
{
    QList<QPair<QString, QStringList>> result;
    
    QSqlQuery query("SELECT group_name, channels FROM channel_groups");
    if (query.exec()) {
        while (query.next()) {
            QString groupName = query.value(0).toString();
            QString channelsStr = query.value(1).toString();
            QStringList channels = channelsStr.split(",");
            
            result.append(qMakePair(groupName, channels));
        }
    }
    
    return result;
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

// Channel Group Management Methods

void UserManagement::onAddChannelGroupClicked()
{
    if (!validateChannelGroupInput()) {
        return;
    }

    QString groupName = groupNameEdit->text();
    QStringList selectedChannels = getSelectedChannels();
    
    if (selectedChannels.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select at least one channel!");
        return;
    }

    // Check if group name already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT group_name FROM channel_groups WHERE group_name = ?");
    checkQuery.addBindValue(groupName);
    
    if (checkQuery.exec() && checkQuery.next()) {
        QMessageBox::warning(this, "Error", "Group name already exists!");
        return;
    }

    // Add new channel group
    QSqlQuery query;
    query.prepare("INSERT INTO channel_groups (group_name, channels) VALUES (?, ?)");
    query.addBindValue(groupName);
    query.addBindValue(selectedChannels.join(","));

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Channel group added successfully!");
        clearChannelGroupForm();
        refreshChannelGroupList();
        emit channelGroupsChanged();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add channel group: " + query.lastError().text());
    }
}

void UserManagement::onEditChannelGroupClicked()
{
    if (currentChannelGroupRow < 0 || !validateChannelGroupInput()) {
        return;
    }

    QString groupName = groupNameEdit->text();
    QStringList selectedChannels = getSelectedChannels();
    
    if (selectedChannels.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select at least one channel!");
        return;
    }

    QString currentGroupName = channelGroupTable->item(currentChannelGroupRow, 0)->text();

    // Update channel group
    QSqlQuery query;
    query.prepare("UPDATE channel_groups SET group_name = ?, channels = ? WHERE group_name = ?");
    query.addBindValue(groupName);
    query.addBindValue(selectedChannels.join(","));
    query.addBindValue(currentGroupName);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Channel group updated successfully!");
        clearChannelGroupForm();
        refreshChannelGroupList();
        emit channelGroupsChanged();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update channel group: " + query.lastError().text());
    }
}

void UserManagement::onDeleteChannelGroupClicked()
{
    if (currentChannelGroupRow < 0) {
        return;
    }

    QString groupName = channelGroupTable->item(currentChannelGroupRow, 0)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete",
        "Are you sure you want to delete channel group: " + groupName + "?",
        QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM channel_groups WHERE group_name = ?");
        query.addBindValue(groupName);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Channel group deleted successfully!");
            clearChannelGroupForm();
            refreshChannelGroupList();
            emit channelGroupsChanged();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete channel group: " + query.lastError().text());
        }
    }
}

void UserManagement::onChannelGroupTableItemClicked(int row, int column)
{
    currentChannelGroupRow = row;
    groupNameEdit->setText(channelGroupTable->item(row, 0)->text());
    
    // Get channels for this group
    QString channelsStr = channelGroupTable->item(row, 1)->text();
    QStringList channels = channelsStr.split(",");
    
    // Reset checkboxes
    channel1Check->setChecked(false);
    channel2Check->setChecked(false);
    channel3Check->setChecked(false);
    channel4Check->setChecked(false);
    
    // Set checkboxes based on channels
    if (channels.contains("1")) channel1Check->setChecked(true);
    if (channels.contains("2")) channel2Check->setChecked(true);
    if (channels.contains("3")) channel3Check->setChecked(true);
    if (channels.contains("4")) channel4Check->setChecked(true);
    
    editChannelGroupButton->setEnabled(true);
    deleteChannelGroupButton->setEnabled(true);
    addChannelGroupButton->setEnabled(false);
}

void UserManagement::clearChannelGroupForm()
{
    groupNameEdit->clear();
    channel1Check->setChecked(false);
    channel2Check->setChecked(false);
    channel3Check->setChecked(false);
    channel4Check->setChecked(false);
    currentChannelGroupRow = -1;
    
    editChannelGroupButton->setEnabled(false);
    deleteChannelGroupButton->setEnabled(false);
    addChannelGroupButton->setEnabled(true);
}

bool UserManagement::validateChannelGroupInput()
{
    if (groupNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Group name cannot be empty!");
        return false;
    }

    if (!channel1Check->isChecked() && !channel2Check->isChecked() && 
        !channel3Check->isChecked() && !channel4Check->isChecked()) {
        QMessageBox::warning(this, "Validation Error", "Please select at least one channel!");
        return false;
    }

    return true;
}

QStringList UserManagement::getSelectedChannels()
{
    QStringList channels;
    if (channel1Check->isChecked()) channels << "1";
    if (channel2Check->isChecked()) channels << "2";
    if (channel3Check->isChecked()) channels << "3";
    if (channel4Check->isChecked()) channels << "4";
    return channels;
}
