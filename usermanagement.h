#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QWidget>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QHeaderView>
#include <QCheckBox>
#include <QTabWidget>
#include <QScrollArea>
#include <QMap>

namespace Ui {
class UserManagement;
}

class UserManagement : public QWidget
{
    Q_OBJECT

public:
    explicit UserManagement(QWidget *parent = nullptr);
    ~UserManagement();
    void refreshUserList();
    void refreshChannelGroupList();
    void refreshAssignmentList();
    void setSessionToken(const QString &token);
    
    // Static methods to get data for other widgets
    static QList<QPair<QString, QStringList>> getChannelGroups();
    static QStringList getUserAssignedChannels(const QString &username);
    static bool isUserAdmin(const QString &username);

signals:
    void channelGroupsChanged();
    void userAssignmentsChanged();

private slots:
    // User management slots
    void onAddUserClicked();
    void onEditUserClicked();
    void onDeleteUserClicked();
    void onTableItemClicked(int row, int column);
    void clearForm();
    
    // Channel group management slots
    void onAddChannelGroupClicked();
    void onEditChannelGroupClicked();
    void onDeleteChannelGroupClicked();
    void onChannelGroupTableItemClicked(int row, int column);
    void clearChannelGroupForm();
    
    // Channel management slots
    void onAddChannelClicked();
    void onDeleteChannelClicked(int channelId);
    void loadAvailableChannels();
    
    // User assignment slots
    void onAssignButtonClicked();
    void onUnassignButtonClicked();
    void onAssignmentTableItemClicked(int row, int column);
    void loadUsersInCombo();
    void loadGroupsInCombo();

private:
    Ui::UserManagement *ui;
    QString sessionToken;
    
    // User management variables
    QTableWidget *userTable;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QComboBox *roleCombo;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *clearButton;
    int currentEditingRow = -1;
    
    // Channel group management variables
    QTableWidget *channelGroupTable;
    QLineEdit *groupNameEdit;
    QPushButton *addChannelGroupButton;
    QPushButton *editChannelGroupButton;
    QPushButton *deleteChannelGroupButton;
    QPushButton *clearChannelGroupButton;
    int currentChannelGroupRow = -1;
    
    // Channel management variables
    QLineEdit *newChannelEdit;
    QPushButton *addChannelButton;
    QWidget *channelsContainer;
    QVBoxLayout *channelsContainerLayout;
    QMap<int, QCheckBox*> channelCheckboxes;
    QMap<int, QPushButton*> channelDeleteButtons;
    
    // User assignment variables
    QTableWidget *assignmentTable;
    QComboBox *assignUserCombo;
    QComboBox *assignGroupCombo;
    QPushButton *assignButton;
    QPushButton *unassignButton;
    int currentAssignmentRow = -1;
    
    void setupUI();
    void setupConnections();
    bool validateInput();
    bool validateChannelGroupInput();
    void updateButtonStates();
    void updateChannelGroupButtonStates();
    
    // Helper methods for channel management
    void addChannelCheckbox(int channelId, const QString &channelName);
    QStringList getSelectedChannels();
    void clearChannelCheckboxes();
};

#endif // USERMANAGEMENT_H
