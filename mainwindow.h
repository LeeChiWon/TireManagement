#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "define.h"

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
   // void on_actionExit_triggered();

    void on_actionExit_triggered();

private:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);

private:
    Ui::MainWindow *ui;    
    QSystemTrayIcon *TrayIcon;
    QMenu *TrayIconMenu;

    void TrayIconInit();

};

#endif // MAINWINDOW_H
