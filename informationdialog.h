#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(QWidget *parent = 0);
    ~InformationDialog();

private slots:
    void on_pushButton_Ok_clicked();
    void reject();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::InformationDialog *ui;

    bool IsReject;
};

#endif // INFORMATIONDIALOG_H
