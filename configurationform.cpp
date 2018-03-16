#include "configurationform.h"
#include "ui_configurationform.h"

ConfigurationForm::ConfigurationForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationForm),IsReject(false)
{
    ui->setupUi(this);
    ComboInit();
    SettingInit();
    if(!IsDatabase())
    {
        DBCreate();
    }
}

ConfigurationForm::~ConfigurationForm()
{
    delete ui;
}

void ConfigurationForm::on_pushButton_Ok_clicked()
{
    SettingSave();
    this->close();
}

void ConfigurationForm::on_pushButton_Cancel_clicked()
{
    this->close();
}

void ConfigurationForm::reject()
{
    if(IsReject)
    {
        QDialog::reject();
    }
}

void ConfigurationForm::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void ConfigurationForm::SettingInit()
{
    Setting=new QSettings("EachOne","TireManagement",this);
    ui->lineEdit_Database_BackupCycle->setText(Setting->value("config/Database/BackupCycle").toString());
    ui->comboBox_Database_BackupCycle->setCurrentIndex(Setting->value("config/Database/BackupCycleType").toInt());
    ui->lineEdit_Database_BackupPath->setText(Setting->value("config/Database/BackupPath").toString());
    ui->lineEdit_Database_Path->setText(Setting->value("config/Database/Path").toString());
}

void ConfigurationForm::ComboInit()
{
    ui->comboBox_Database_BackupCycle->clear();
    ui->comboBox_Database_BackupCycle->addItems(QStringList()<<tr("Hour")<<tr("Day")<<tr("Week")<<tr("Month")<<tr("Year"));
}

void ConfigurationForm::SettingSave()
{
    Setting->setValue("config/Database/BackupCycle",ui->lineEdit_Database_BackupCycle->text());
    Setting->setValue("config/Database/BackupCycleType",ui->comboBox_Database_BackupCycle->currentIndex());
    Setting->setValue("config/Database/BackupPath",ui->lineEdit_Database_BackupPath->text());
    Setting->setValue("config/Database/Path",ui->lineEdit_Database_Path->text());
}

void ConfigurationForm::DBCreate()
{
    if(!Setting->value("config/Database/Path").toString().isEmpty())
    {
        QSqlDatabase DB=QSqlDatabase::addDatabase("QSQLITE","DB");
        DB.setDatabaseName(Setting->value("config/Database/Path").toString());

        if(!DB.open())
        {
            QSqlDatabase::removeDatabase("DB");
            return;
        }

        QSqlQuery query(DB);
        QString QueryStr=QString("CREATE TABLE IF NOT EXISTS 'login_tb' ('UserID' TEXT NOT NULL, 'Password' TEXT NOT NULL, PRIMARY KEY('UserID'));");
        query.exec(QueryStr);

        QSqlDatabase::removeDatabase("DB");
        DB.close();
    }
}

bool ConfigurationForm::IsDatabase()
{
    QFileInfo FileInfo(Setting->value("config/Database/Path").toString());
    if(!FileInfo.exists())
    {
        return false;
    }
    return true;
}

void ConfigurationForm::on_pushButton_Database_Path_clicked()
{
    ui->lineEdit_Database_Path->setText(QFileDialog::getExistingDirectory(this,tr("Choose Directory"),NULL,QFileDialog::ShowDirsOnly));
}

void ConfigurationForm::on_pushButton_Database_BackupPath_clicked()
{
    ui->lineEdit_Database_BackupPath->setText(QFileDialog::getExistingDirectory(this,tr("Choose Directory"),NULL,QFileDialog::ShowDirsOnly));
}
