#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TrayIconInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TrayIconInit()
{
    TrayIcon=new QSystemTrayIcon(this);
    TrayIconMenu=new QMenu(this);
    TrayIconMenu->addAction(ui->actionExit);
    TrayIconMenu->addSeparator();
    TrayIcon->setContextMenu(TrayIconMenu);
    QIcon Icon(":img/tire.png");
    TrayIcon->setIcon(Icon);
    TrayIcon->show();
    TrayIcon->setToolTip(tr("TireManagement"));
    TrayIcon->showMessage(tr("TireManagement"),tr("Executing..."),QSystemTrayIcon::Information,5000);
    connect(TrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(onSystemTryIconClicked(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::onSystemTryIconClicked(QSystemTrayIcon::ActivationReason reason){
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this->setWindowState(Qt::WindowActive);
        this->show();
        break;
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->hide();
    this->close();
}

void MainWindow::hideEvent(QHideEvent *event)
{
    if(isMinimized())
    {
        this->hide();
    }
    QWidget::hideEvent(event);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(TrayIcon->isVisible())
    {
        TrayIcon->hide();
    }
    QWidget::closeEvent(event);
}
