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
    bool QueryError=false;
    if(!ui->lineEdit_UserID->isEnabled())
    {
        ui->lineEdit_UserID->setEnabled(true);
        ui->lineEdit_UserID->setText("");
        ui->lineEdit_Password->setText("");
        return;
    }

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
            ui->lineEdit_UserID->setEnabled(true);
            QueryError=true;
            break;
        }
        QSqlDatabase::database().commit();
        refreshModel();
    }
    ui->lineEdit_UserID->setEnabled(!QueryError);
}

void AdminModeDialog::on_pushButton_Modify_clicked()
{
    QueryExec(QString("UPDATE login_tb SET password='%2' WHERE UserID='%1'")
              .arg(ui->lineEdit_UserID->text(),crypto.encryptToString(ui->lineEdit_Password->text())));
}

void AdminModeDialog::on_pushButton_Delete_clicked()
{
    QueryExec(QString("DELETE FROM login_tb WHERE UserID='%1'")
              .arg(ui->lineEdit_UserID->text()));
}

void AdminModeDialog::on_pushButton_Find_clicked()
{
    if(!ui->lineEdit_UserID->isEnabled())
    {
        ui->lineEdit_UserID->setEnabled(true);
        ui->lineEdit_UserID->setText("");
        ui->lineEdit_Password->setText("");
        return;
    }

    if(ui->lineEdit_UserID->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Result"),tr("UserID is empty."));
        return;
    }
    Model->clear();
    Model->setQuery(QString("SELECT * FROM login_tb where UserID='%1'").arg(ui->lineEdit_UserID->text()),DB);
    qDebug()<<Model->query().lastQuery()<<Model->query().lastError().text();
    if(ui->tableView->model()->rowCount()<=0)
    {
        QMessageBox::warning(this,tr("Result"),tr("No results found."));
        Model->clear();
        Model->setQuery("SELECT * FROM login_tb",DB);
    }
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
    query.exec(QString("SELECT * FROM login_tb WHERE UserID='%1'")
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
    ui->pushButton_Modify->setEnabled(false);
    ui->pushButton_Delete->setEnabled(false);
}

void AdminModeDialog::QueryExec(const QString &QueryStr)
{
    if(ui->lineEdit_UserID->text().isEmpty())
    {
        QMessageBox::warning(this,tr("Result"),tr("UserID is empty."));
        return;
    }
    QSqlDatabase::database().transaction();
    QSqlQuery query(DB);
    query.exec(QueryStr);
    switch(query.lastError().number())
    {
    case QSqlError::NoError:
    case QSqlError::NoError-1:
        break;
    default:
        QMessageBox::critical(this,tr("Error"),query.lastError().text());
        break;
    }
    QSqlDatabase::database().commit();
    refreshModel();
}

void AdminModeDialog::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_UserID->setText(ui->tableView->model()->index(index.row(),0).data().toString());
    ui->lineEdit_Password->setText(ui->tableView->model()->index(index.row(),1).data().toString());
    ui->pushButton_Modify->setEnabled(true);
    ui->pushButton_Delete->setEnabled(true);
    ui->lineEdit_UserID->setEnabled(false);
}
