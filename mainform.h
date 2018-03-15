#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QtWidgets>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
