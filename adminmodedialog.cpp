#include "adminmodedialog.h"
#include "ui_adminmodedialog.h"

AdminModeDialog::AdminModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminModeDialog)
{
    ui->setupUi(this);
    crypto.setKey(Q_UINT64_C(0x010a020b030c));
    TableViewInit();

}

AdminModeDialog::~AdminModeDialog()
{
    DB.close();
    QSqlDatabase::removeDatabase("ADMINDB");
    delete ui;
}

void AdminModeDialog::on_pushButton_New_clicked()
{
    if(!isUserIDCheck())
    {
        QSqlDatabase::database().transaction();
        QSqlQuery query(DB);
        query.exec(QString("insert into login_tb values('%1','%2')")
                        .arg(ui->lineEdit_UserID->text(),crypto.encryptToString(ui->lineEdit_Password->text())));

        switch(query.lastError().number())
        {
        case QSqlError::NoError:
        case QSqlError::NoError-1:
            break;
        case 19:
            QMessageBox::critical(this,tr("Error"),tr("UserID is duplicate."));
            return;
            break;
        }
        QSqlDatabase::database().commit();
        refreshModel();
    }
}

void AdminModeDialog::on_pushButton_Modify_clicked()
{

}

void AdminModeDialog::on_pushButton_Delete_clicked()
{

}

void AdminModeDialog::on_pushButton_Find_clicked()
{

}

void AdminModeDialog::on_pushButton_Return_clicked()
{
    refreshModel();
}

void AdminModeDialog::TableViewInit()
{
    Setting=new QSettings("EachOne","TireManagement",this);
    DB=QSqlDatabase::addDatabase("QSQLITE","ADMINDB");
    DB.setDatabaseName(Setting->value("config/Database/Path").toString());

    if(!DB.open())
    {
        QMessageBox::critical(this,tr("Error"),tr("DB Open Failed."));
        QSqlDatabase::removeDatabase("ADMINDB");
        return;
    }

    Model=new QSqlQueryModel;
    Model->setQuery("SELECT * FROM login_tb",DB);
    Model->setHeaderData(0,Qt::Horizontal,tr("UserID"));
    Model->setHeaderData(1,Qt::Horizontal,tr("Password"));

    ui->tableView->setModel(Model);
    ui->tableView->show();
}

bool AdminModeDialog::isUserIDCheck()
{
    QSqlQuery query(DB);
    query.exec(QString("SELECT * FROM login_tb WHERE user_id='%1'")
               .arg(ui->lineEdit_UserID->text()));
    if(query.next())
    {
        QMessageBox::warning(this,tr("Warning"),tr("UserID is duplicate."));
        return true;
    }
    return false;
}

void AdminModeDialog::refreshModel()
{
    Model->clear();
    Model->setQuery("SELECT * FROM login_tb",DB);
    ui->lineEdit_Password->setText("");
    ui->lineEdit_UserID->setText("");
}

