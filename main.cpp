#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator Translator;
    if(!Translator.load(":/translator/Lang_ko_KR.qm"))
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("Language Change Failed."));
        msgBox.setWindowTitle(QObject::tr("TireManagement"));
        msgBox.show();
    }
    QApplication::installTranslator(&Translator);

    MainWindow w;
    QSharedMemory shared("TireManagement");
    if(!shared.create(512,QSharedMemory::ReadWrite))
    {
        QMessageBox::information(&w,QObject::tr("TireManagement"),QObject::tr("Executing..."),QMessageBox::Ok);
        exit(0);
    }   
    QSplashScreen *splashScreen=new QSplashScreen;
    splashScreen->setPixmap(QPixmap(":/img/waiting.png"));
    splashScreen->show();
    QTimer::singleShot(1000,splashScreen,SLOT(close()));
    LoginDialog loginDlg;
    QObject::connect(&loginDlg,SIGNAL(LoginOK()),&w,SLOT(show()));
    QObject::connect(&loginDlg,SIGNAL(LoginOK()),&w,SLOT(isAdmin()));
    QTimer::singleShot(1000,&loginDlg,SLOT(show()));

   // loginDlg.show();
    return a.exec();
}
