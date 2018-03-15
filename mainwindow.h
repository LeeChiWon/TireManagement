#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "define.h"
#include "informationdialog.h"
#include "mainform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onSystemTryIconClicked(QSystemTrayIcon::ActivationReason);
    void on_actionExit_triggered();
    void on_actionInformation_triggered();
    void on_actionMain_triggered();
    void on_tabWidget_tabCloseRequested(int index);

private:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);

private:
    Ui::MainWindow *ui;    
    QSystemTrayIcon *TrayIcon;
    QMenu *TrayIconMenu;
    QSettings *Setting;

    void TrayIconInit();
    void SettingInit();
    void TabInit();
    bool isTabEnabled(const QString &TabName);
};

#endif // MAINWINDOW_H
