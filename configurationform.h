#ifndef CONFIGURATIONFORM_H
#define CONFIGURATIONFORM_H

#include <QDialog>
#include <QtWidgets>
#include "define.h"

namespace Ui {
class ConfigurationForm;
}

class ConfigurationForm : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationForm(QWidget *parent = 0);
    ~ConfigurationForm();

private slots:
    void on_pushButton_Ok_clicked();
    void on_pushButton_Cancel_clicked();
    void reject();
    void on_pushButton_Database_Path_clicked();
    void on_pushButton_Database_BackupPath_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ConfigurationForm *ui;
    QSettings *Setting;
    bool IsReject;

    void SettingInit();
    void ComboInit();
    void SettingSave();
    void DBCreate();
    bool IsDatabase();
};

#endif // CONFIGURATIONFORM_H
