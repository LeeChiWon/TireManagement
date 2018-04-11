#include "logindialog.h"
#include "ui_logindialog.h"

QString g_UserID;
QString g_Password;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    IsReject(false),iXdifferent(-1),iYdifferent(-1),b_MousePressed(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    crypto.setKey(Q_UINT64_C(0x010a020b030c));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::DBInit(const QString &UserID, const QString &Password)
{
    Setting=new QSettings("EachOne","TireManagement",this);   
    if(Setting->value("config/Database/Path").toString().isEmpty())
    {
        QMessageBox::critical(this,tr("Error"),tr("DB is not found."));
        return false;
    }

    QSqlDatabase DB=QSqlDatabase::addDatabase("QSQLITE","DB");
    DB.setDatabaseName(Setting->value("config/Database/Path").toString());

    if(!DB.open())
    {
        QMessageBox::critical(this,tr("Error"),tr("DB Open Failed."));
        QSqlDatabase::removeDatabase("DB");
        return false;
    }

    QSqlQuery query(DB);
    query.exec(QString("select password from login_tb where UserID='%1'").arg(UserID));
    if(!query.next())
    {
        DB.close();
        return false;
    }

    if(query.lastError().number()>QSqlError::NoError)
    {
        QString ErrorText=QString("%1 - %2").arg(query.lastError().number()).arg(query.lastError().text());
        QMessageBox::critical(this,tr("DB Error"),ErrorText);
        QSqlDatabase::removeDatabase("DB");
    }

    QString DecryptPassword=crypto.decryptToString(query.value("password").toString());

    DB.close();    
    if(Password==DecryptPassword)
    {
        g_UserID=UserID;
    }
    return Password!=DecryptPassword? false:true;

    /*QString QueryStr=QString("select * from login_tb where UserID='%1' and password='%2'").arg(UserID,crypto.encryptToString(ui->lineEdit_Password->text()));

    query.exec(QueryStr);
    if(query.next())
    {
        DB.close();
        g_UserID=UserID;
        //g_Password=Password;
        g_Password=Password;
        return true;
    }


    DB.close();*/

}


bool LoginDialog::isLogin(const QString &UserID, const QString &Password)
{    
    if(UserID==MASTER_ID)
    {
        if(Password==MASTER_PASSWORD)
        {
            g_UserID=UserID;
            return true;
        }
        return false;
    }
    return DBInit(UserID,Password);
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


