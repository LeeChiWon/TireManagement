#include "configurationform.h"
#include "ui_configurationform.h"

ConfigurationForm::ConfigurationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigurationForm)
{
    ui->setupUi(this);
}

ConfigurationForm::~ConfigurationForm()
{
    delete ui;
}

void ConfigurationForm::on_pushButton_Ok_clicked()
{

}

void ConfigurationForm::on_pushButton_Cancel_clicked()
{

}

void ConfigurationForm::on_pushButton_DatabasePath_clicked()
{
    ui->lineEdit_DatabasePath->setText(QFileDialog::getExistingDirectory(this,tr("Choose Directory"),NULL,QFileDialog::ShowDirsOnly));
}
