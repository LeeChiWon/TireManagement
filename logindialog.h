#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "define.h"
#include "simplecrypt.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
     void LoginOK();

protected:
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
     void on_pushButton_Login_clicked();
     void on_pushButton_Cancel_clicked();
     void reject();

private:
    Ui::LoginDialog *ui;
    bool IsReject;
    int iXdifferent,iYdifferent;
    bool b_MousePressed;
    QSettings *Setting;
    SimpleCrypt crypto;

    bool DBInit(const QString &UserID, const QString &Password);
    bool isLogin(const QString &UserID, const QString &Password);
};

#endif // LOGINDIALOG_H
