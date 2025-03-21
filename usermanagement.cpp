#include "usermanagement.h"
#include "ui_usermanagement.h"
#include <QCryptographicHash>
#include <QSqlError>
#include <QDebug>
#include <QHBoxLayout>

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
    addChannelGroupButton = ui->addChannelGroupButton;
    editChannelGroupButton = ui->editChannelGroupButton;
    deleteChannelGroupButton = ui->deleteChannelGroupButton;
    clearChannelGroupButton = ui->clearChannelGroupButton;
    
    // Initialize channel management
    channelsContainer = ui->channelsContainer;
    channelsContainerLayout = qobject_cast<QVBoxLayout*>(channelsContainer->layout());
    newChannelEdit = ui->newChannelEdit;
    addChannelButton = ui->addChannelButton;
    
    // Get references to UI elements for user assignments
    assignmentTable = ui->assignmentTable;
    assignUserCombo = ui->assignUserCombo;
    assignGroupCombo = ui->assignGroupCombo;
    assignButton = ui->assignButton;
    unassignButton = ui->unassignButton;
    
    // Set up initial button states
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);
    editChannelGroupButton->setEnabled(false);
    deleteChannelGroupButton->setEnabled(false);
    unassignButton->setEnabled(false);
    
    // Connect signals
    connect(addButton, &QPushButton::clicked, this, &UserManagement::onAddUserClicked);
    connect(editButton, &QPushButton::clicked, this, &UserManagement::onEditUserClicked);
    connect(deleteButton, &QPushButton::clicked, this, &UserManagement::onDeleteUserClicked);
    connect(clearButton, &QPushButton::clicked, this, &UserManagement::clearForm);
    connect(userTable, &QTableWidget::cellClicked, this, &UserManagement::onTableItemClicked);
    
    connect(addChannelGroupButton, &QPushButton::clicked, this, &UserManagement::onAddChannelGroupClicked);
    connect(editChannelGroupButton, &QPushButton::clicked, this, &UserManagement::onEditChannelGroupClicked);
    connect(deleteChannelGroupButton, &QPushButton::clicked, this, &UserManagement::onDeleteChannelGroupClicked);
    connect(clearChannelGroupButton, &QPushButton::clicked, this, &UserManagement::clearChannelGroupForm);
    connect(channelGroupTable, &QTableWidget::cellClicked, this, &UserManagement::onChannelGroupTableItemClicked);
    
    connect(addChannelButton, &QPushButton::clicked, this, &UserManagement::onAddChannelClicked);
    
    connect(assignButton, &QPushButton::clicked, this, &UserManagement::onAssignButtonClicked);
    connect(unassignButton, &QPushButton::clicked, this, &UserManagement::onUnassignButtonClicked);
    connect(assignmentTable, &QTableWidget::cellClicked, this, &UserManagement::onAssignmentTableItemClicked);
    
    // Load initial data
    loadAvailableChannels();
    refreshUserList();
    refreshChannelGroupList();
    loadUsersInCombo();
    loadGroupsInCombo();
    refreshAssignmentList();
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

void UserManagement::refreshAssignmentList()
{
    assignmentTable->setRowCount(0);
    QSqlQuery query("SELECT username, group_name FROM user_channel_groups ORDER BY username");
    
    if (!query.exec()) {
        QMessageBox::warning(this, "Error", "Failed to fetch user assignments: " + query.lastError().text());
        return;
    }

    while (query.next()) {
        int row = assignmentTable->rowCount();
        assignmentTable->insertRow(row);
        assignmentTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        assignmentTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
    }
}

void UserManagement::loadUsersInCombo()
{
    assignUserCombo->clear();
    QSqlQuery query("SELECT username FROM users WHERE role = 'user' ORDER BY username");
    
    if (query.exec()) {
        while (query.next()) {
            assignUserCombo->addItem(query.value(0).toString());
        }
    }
}

void UserManagement::loadGroupsInCombo()
{
    assignGroupCombo->clear();
    QSqlQuery query("SELECT group_name FROM channel_groups ORDER BY group_name");
    
    if (query.exec()) {
        while (query.next()) {
            assignGroupCombo->addItem(query.value(0).toString());
        }
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

QStringList UserManagement::getUserAssignedChannels(const QString &username)
{
    QStringList result;
    QSet<QString> uniqueChannels;
    
    QSqlQuery query;
    query.prepare("SELECT cg.channels FROM user_channel_groups ucg "
                 "JOIN channel_groups cg ON ucg.group_name = cg.group_name "
                 "WHERE ucg.username = :username");
    query.bindValue(":username", username);
    
    if (query.exec()) {
        while (query.next()) {
            QString channels = query.value(0).toString();
            QStringList channelList = channels.split(",", Qt::SkipEmptyParts);
            for (const QString &channel : channelList) {
                uniqueChannels.insert(channel.trimmed());
            }
        }
    }
    
    // Convert QSet to QStringList manually
    foreach (const QString &channel, uniqueChannels) {
        result.append(channel);
    }
    
    return result;
}

bool UserManagement::isUserAdmin(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (query.exec() && query.next()) {
        return query.value(0).toString() == "admin";
    }
    
    return false;
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
        loadUsersInCombo(); // Refresh the user combo box in assignments tab
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
        // If username changed, update user_channel_groups table
        if (username != currentUsername) {
            QSqlQuery updateAssignments;
            updateAssignments.prepare("UPDATE user_channel_groups SET username = ? WHERE username = ?");
            updateAssignments.addBindValue(username);
            updateAssignments.addBindValue(currentUsername);
            updateAssignments.exec();
        }
        
        QMessageBox::information(this, "Success", "User updated successfully!");
        clearForm();
        refreshUserList();
        loadUsersInCombo(); // Refresh the user combo box in assignments tab
        refreshAssignmentList(); // Refresh assignments if username changed
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
            loadUsersInCombo(); // Refresh the user combo box in assignments tab
            refreshAssignmentList(); // Refresh assignments as user was deleted
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
        loadGroupsInCombo(); // Refresh the group combo box in assignments tab
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
        // If group name changed, update user_channel_groups table
        if (groupName != currentGroupName) {
            QSqlQuery updateAssignments;
            updateAssignments.prepare("UPDATE user_channel_groups SET group_name = ? WHERE group_name = ?");
            updateAssignments.addBindValue(groupName);
            updateAssignments.addBindValue(currentGroupName);
            updateAssignments.exec();
        }
        
        QMessageBox::information(this, "Success", "Channel group updated successfully!");
        clearChannelGroupForm();
        refreshChannelGroupList();
        loadGroupsInCombo(); // Refresh the group combo box in assignments tab
        refreshAssignmentList(); // Refresh assignments if group name changed
        emit channelGroupsChanged();
        emit userAssignmentsChanged();
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
            loadGroupsInCombo(); // Refresh the group combo box in assignments tab
            refreshAssignmentList(); // Refresh assignments as group was deleted
            emit channelGroupsChanged();
            emit userAssignmentsChanged();
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
    QStringList selectedChannels = channelsStr.split(",");
    
    // Reset all checkboxes
    for (QCheckBox *checkbox : channelCheckboxes) {
        checkbox->setChecked(false);
    }
    
    // Set selected checkboxes
    for (const QString &channelId : selectedChannels) {
        if (channelCheckboxes.contains(channelId.toInt())) {
            channelCheckboxes[channelId.toInt()]->setChecked(true);
        }
    }
    
    editChannelGroupButton->setEnabled(true);
    deleteChannelGroupButton->setEnabled(true);
    addChannelGroupButton->setEnabled(false);
}

void UserManagement::clearChannelGroupForm()
{
    groupNameEdit->clear();
    
    // Uncheck all checkboxes
    for (QCheckBox *checkbox : channelCheckboxes) {
        checkbox->setChecked(false);
    }
    
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

    bool hasSelectedChannel = false;
    for (QCheckBox *checkbox : channelCheckboxes) {
        if (checkbox->isChecked()) {
            hasSelectedChannel = true;
            break;
        }
    }
    
    if (!hasSelectedChannel) {
        QMessageBox::warning(this, "Validation Error", "Please select at least one channel!");
        return false;
    }

    return true;
}

QStringList UserManagement::getSelectedChannels()
{
    QStringList channels;
    for (auto it = channelCheckboxes.begin(); it != channelCheckboxes.end(); ++it) {
        if (it.value()->isChecked()) {
            channels << QString::number(it.key());
        }
    }
    return channels;
}

// User Assignment Methods

void UserManagement::onAssignButtonClicked()
{
    if (assignUserCombo->count() == 0 || assignGroupCombo->count() == 0) {
        QMessageBox::warning(this, "Error", "No users or channel groups available for assignment!");
        return;
    }
    
    QString username = assignUserCombo->currentText();
    QString groupName = assignGroupCombo->currentText();
    
    // Check if assignment already exists
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM user_channel_groups WHERE username = ? AND group_name = ?");
    checkQuery.addBindValue(username);
    checkQuery.addBindValue(groupName);
    
    if (checkQuery.exec() && checkQuery.next()) {
        QMessageBox::warning(this, "Error", "This user is already assigned to this channel group!");
        return;
    }
    
    // Add new assignment
    QSqlQuery query;
    query.prepare("INSERT INTO user_channel_groups (username, group_name) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(groupName);
    
    if (query.exec()) {
        QMessageBox::information(this, "Success", "Channel group assigned to user successfully!");
        refreshAssignmentList();
        emit userAssignmentsChanged();
    } else {
        QMessageBox::warning(this, "Error", "Failed to assign channel group: " + query.lastError().text());
    }
}

void UserManagement::onUnassignButtonClicked()
{
    if (currentAssignmentRow < 0) {
        return;
    }
    
    QString username = assignmentTable->item(currentAssignmentRow, 0)->text();
    QString groupName = assignmentTable->item(currentAssignmentRow, 1)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Removal",
        "Are you sure you want to remove the assignment of channel group '" + groupName + 
        "' from user '" + username + "'?",
        QMessageBox::Yes|QMessageBox::No);
        
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM user_channel_groups WHERE username = ? AND group_name = ?");
        query.addBindValue(username);
        query.addBindValue(groupName);
        
        if (query.exec()) {
            QMessageBox::information(this, "Success", "Assignment removed successfully!");
            currentAssignmentRow = -1;
            unassignButton->setEnabled(false);
            refreshAssignmentList();
            emit userAssignmentsChanged();
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove assignment: " + query.lastError().text());
        }
    }
}

void UserManagement::onAssignmentTableItemClicked(int row, int column)
{
    currentAssignmentRow = row;
    unassignButton->setEnabled(true);
    
    // Set the combo boxes to the selected values
    QString username = assignmentTable->item(row, 0)->text();
    QString groupName = assignmentTable->item(row, 1)->text();
    
    int userIndex = assignUserCombo->findText(username);
    if (userIndex >= 0) {
        assignUserCombo->setCurrentIndex(userIndex);
    }
    
    int groupIndex = assignGroupCombo->findText(groupName);
    if (groupIndex >= 0) {
        assignGroupCombo->setCurrentIndex(groupIndex);
    }
}

void UserManagement::onAddChannelClicked()
{
    QString channelName = newChannelEdit->text().trimmed();
    if (channelName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a channel name!");
        return;
    }
    
    // Get next available channel ID
    QSqlQuery maxIdQuery;
    int nextId = 1;
    if (maxIdQuery.exec("SELECT COALESCE(MAX(channel_id), 0) FROM channels")) {
        if (maxIdQuery.next()) {
            nextId = maxIdQuery.value(0).toInt() + 1;
        }
    }
    
    // Add channel to database
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO channels (channel_id, channel_name) VALUES (?, ?)");
    insertQuery.addBindValue(nextId);
    insertQuery.addBindValue(channelName);
    
    if (insertQuery.exec()) {
        addChannelCheckbox(nextId, channelName);
        newChannelEdit->clear();
        QMessageBox::information(this, "Success", "Channel added successfully!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to add channel: " + insertQuery.lastError().text());
    }
}

void UserManagement::onDeleteChannelClicked(int channelId)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete",
        "Are you sure you want to delete this channel? This will also remove it from any channel groups.",
        QMessageBox::Yes|QMessageBox::No);
        
    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM channels WHERE channel_id = ?");
        query.addBindValue(channelId);
        
        if (query.exec()) {
            // Remove checkbox and delete button
            if (channelCheckboxes.contains(channelId)) {
                delete channelCheckboxes[channelId];
                channelCheckboxes.remove(channelId);
            }
            if (channelDeleteButtons.contains(channelId)) {
                delete channelDeleteButtons[channelId];
                channelDeleteButtons.remove(channelId);
            }
            
            // Refresh channel groups that might have contained this channel
            refreshChannelGroupList();
            emit channelGroupsChanged();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete channel: " + query.lastError().text());
        }
    }
}

void UserManagement::loadAvailableChannels()
{
    clearChannelCheckboxes();
    
    QSqlQuery query;
    if (query.exec("SELECT channel_id, channel_name FROM channels ORDER BY channel_id")) {
        while (query.next()) {
            int channelId = query.value(0).toInt();
            QString channelName = query.value(1).toString();
            addChannelCheckbox(channelId, channelName);
        }
    } else {
        qDebug() << "Error loading channels:" << query.lastError().text();
    }
}

void UserManagement::addChannelCheckbox(int channelId, const QString &channelName)
{
    // Create container widget for checkbox and delete button
    QWidget *container = new QWidget(channelsContainer);
    QHBoxLayout *layout = new QHBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    
    // Create checkbox
    QCheckBox *checkbox = new QCheckBox(channelName, container);
    layout->addWidget(checkbox);
    
    // Create delete button
    QPushButton *deleteButton = new QPushButton("Delete", container);
    deleteButton->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; padding: 5px 10px; border-radius: 3px; } "
                              "QPushButton:hover { background-color: #c0392b; }");
    layout->addWidget(deleteButton);
    
    // Add spacer to push delete button to the right
    layout->addStretch();
    
    // Store references
    channelCheckboxes[channelId] = checkbox;
    channelDeleteButtons[channelId] = deleteButton;
    
    // Connect delete button
    connect(deleteButton, &QPushButton::clicked, this, [this, channelId]() {
        onDeleteChannelClicked(channelId);
    });
    
    // Add to layout
    channelsContainerLayout->addWidget(container);
}

void UserManagement::clearChannelCheckboxes()
{
    // Clear all existing checkboxes and delete buttons
    qDeleteAll(channelCheckboxes);
    qDeleteAll(channelDeleteButtons);
    channelCheckboxes.clear();
    channelDeleteButtons.clear();
    
    // Clear the layout
    QLayoutItem *child;
    while ((child = channelsContainerLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            delete child->widget();
        }
        delete child;
    }
}
