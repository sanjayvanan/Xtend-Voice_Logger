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
    void setSessionToken(const QString &token);
    
    // Static method to get channel groups for other widgets
    static QList<QPair<QString, QStringList>> getChannelGroups();

signals:
    void channelGroupsChanged();

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
    QCheckBox *channel1Check;
    QCheckBox *channel2Check;
    QCheckBox *channel3Check;
    QCheckBox *channel4Check;
    QPushButton *addChannelGroupButton;
    QPushButton *editChannelGroupButton;
    QPushButton *deleteChannelGroupButton;
    QPushButton *clearChannelGroupButton;
    int currentChannelGroupRow = -1;
    
    void setupUI();
    void setupConnections();
    bool validateInput();
    bool validateChannelGroupInput();
    void updateButtonStates();
    void updateChannelGroupButtonStates();
    
    // Helper method to get selected channels
    QStringList getSelectedChannels();
};

#endif // USERMANAGEMENT_H
