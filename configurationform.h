#ifndef CONFIGURATIONFORM_H
#define CONFIGURATIONFORM_H

#include <QWidget>
#include <QtWidgets>

namespace Ui {
class ConfigurationForm;
}

class ConfigurationForm : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationForm(QWidget *parent = 0);
    ~ConfigurationForm();

private slots:
    void on_pushButton_Ok_clicked();
    void on_pushButton_Cancel_clicked();
    void on_pushButton_DatabasePath_clicked();

private:
    Ui::ConfigurationForm *ui;
    QSettings *Setting;

    void SettingInit();
};

#endif // CONFIGURATIONFORM_H
