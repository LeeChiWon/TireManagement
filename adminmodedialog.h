#ifndef ADMINMODEDIALOG_H
#define ADMINMODEDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "simplecrypt.h"
#include "define.h"

namespace Ui {
class AdminModeDialog;
}

class AdminModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminModeDialog(QWidget *parent = 0);
    ~AdminModeDialog();

private slots:
    void on_pushButton_New_clicked();
    void on_pushButton_Modify_clicked();
    void on_pushButton_Delete_clicked();
    void on_pushButton_Find_clicked();
    void on_pushButton_Return_clicked();

private:
    Ui::AdminModeDialog *ui;
    SimpleCrypt crypto;
    QSettings *Setting;
    QSqlDatabase DB;
    QSqlQueryModel *Model;

    void TableViewInit();
    bool isUserIDCheck();
    void refreshModel();
};

#endif // ADMINMODEDIALOG_H
