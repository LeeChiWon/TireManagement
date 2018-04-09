#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),ApplicationExitType(0)
{
    ui->setupUi(this);
    TrayIconInit();
    SettingInit();
    TabInit();
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

void MainWindow::SettingInit()
{
    Setting=new QSettings("EachOne","TireManagement",this);
    restoreGeometry(Setting->value("config/Geometry").toByteArray());
}

void MainWindow::TabInit()
{
    ui->tabWidget->clear();
    on_actionMain_triggered();
}

bool MainWindow::isTabEnabled(const QString &TabName)
{
    for(int i=0; i<ui->tabWidget->count(); i++)
    {
        if(ui->tabWidget->tabText(i)==TabName)
        {
            ui->tabWidget->setCurrentIndex(i);
            return true;
        }
    }

    return false;
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
    ApplicationExitType=APPLICATION_EXIT;
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
    event->ignore();
    int ret;
    switch (ApplicationExitType) {
    case APPLICATION_EXIT:
        ret= QMessageBox::information(this, tr("Exit"),
                                       tr("Are you exit application?"),
                                       QMessageBox::Ok| QMessageBox::Cancel,
                                       QMessageBox::Ok);
        break;
    default:
        ret= QMessageBox::information(this, tr("Logout"),
                                       tr("Are you Logout application?"),
                                       QMessageBox::Ok| QMessageBox::Cancel,
                                       QMessageBox::Ok);
        break;
    }

    switch(ret)
    {
    case QMessageBox::Ok:
        if(TrayIcon->isVisible())
        {
            TrayIcon->hide();
        }
        Setting->setValue("config/Geometry",saveGeometry());
        event->accept();
        break;
    }
   // QWidget::closeEvent(event);
}

void MainWindow::on_actionInformation_triggered()
{
    InformationDialog InformationDlg;
    InformationDlg.exec();
}

void MainWindow::on_actionMain_triggered()
{
    if(!isTabEnabled(MENU_MAIN))
    {
        MainForm *mainForm=new MainForm;
        ui->tabWidget->addTab(mainForm,MENU_MAIN);
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    auto *Widget=ui->tabWidget->widget(index);
    Widget->deleteLater();
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionConfiguration_triggered()
{
    ConfigurationForm ConfigurationDlg;
    ConfigurationDlg.exec();
}

void MainWindow::on_actionLogout_triggered()
{
    ApplicationExitType=APPLICATION_LOGOUT;
    this->close();
    QString newfilename = QString("%1").arg(QApplication::applicationFilePath());
    QDesktopServices::openUrl(QUrl(newfilename.prepend( "file:///" )));
}
