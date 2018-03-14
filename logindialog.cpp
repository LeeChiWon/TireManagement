#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    IsReject(false),iXdifferent(-1),iYdifferent(-1),b_MousePressed(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::DBInit()
{

}

bool LoginDialog::isLogin(const QString &UserID, const QString &Password)
{
    if(UserID!=MASTER_ID || Password!=MASTER_PASSWORD)
    {
        return false;
    }
    return true;
}

void LoginDialog::on_pushButton_Login_clicked()
{
    if(isLogin(ui->lineEdit_UserID->text(),ui->lineEdit_Password->text()))
    {
        emit LoginOK();
        this->close();
    }

    else
    {
        QMessageBox::critical(this,tr("Login"),tr("UserID or Password is incorrect."));
    }
}

void LoginDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}

void LoginDialog::reject()
{
    if(IsReject)
    {
        QDialog::reject();
    }
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void LoginDialog::mousePressEvent (QMouseEvent * event)
{
    b_MousePressed = true;
    QPoint qpMousePressedPoint = QCursor::pos();
    QPoint qpApploc = this->pos();
    iXdifferent = qpMousePressedPoint.x() - qpApploc.x();
    iYdifferent = qpMousePressedPoint.y() - qpApploc.y();
    QWidget::mousePressEvent(event);
}

void LoginDialog::mouseReleaseEvent (QMouseEvent * event)
{
    b_MousePressed = false;
    QWidget::mouseReleaseEvent(event);
}

void LoginDialog::mouseMoveEvent ( QMouseEvent * event )
{
    if(b_MousePressed)
    {
        QPoint qpAppNewLoc(  (QCursor::pos().x() - iXdifferent) , (QCursor::pos().y() - iYdifferent)  );
        this->setProperty("pos", qpAppNewLoc);
    }
    QWidget::mouseMoveEvent(event);
}


