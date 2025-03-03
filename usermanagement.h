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
    void setSessionToken(const QString &token);

private slots:
    void onAddUserClicked();
    void onEditUserClicked();
    void onDeleteUserClicked();
    void onTableItemClicked(int row, int column);
    void clearForm();

private:
    Ui::UserManagement *ui;
    QString sessionToken;
    QTableWidget *userTable;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QComboBox *roleCombo;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *clearButton;
    
    void setupUI();
    void setupConnections();
    bool validateInput();
    void updateButtonStates();
    int currentEditingRow = -1;
};

#endif // USERMANAGEMENT_H
