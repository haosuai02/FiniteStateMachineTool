#ifndef WIZARDDIALOG_H
#define WIZARDDIALOG_H

#include <QDialog>

namespace Ui {
class WizardDialog;
}

class WizardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WizardDialog(QWidget *parent = nullptr);
    ~WizardDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WizardDialog *ui;
    int numState;
    int numAction;
};

#endif // WIZARDDIALOG_H
