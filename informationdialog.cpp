#include "informationdialog.h"
#include "ui_informationdialog.h"

InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog),IsReject(false)
{
    ui->setupUi(this);    
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

void InformationDialog::on_pushButton_Ok_clicked()
{
    this->close();
}

void InformationDialog::reject()
{
    if(IsReject)
    {
        QDialog::reject();
    }
}

void InformationDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
}
