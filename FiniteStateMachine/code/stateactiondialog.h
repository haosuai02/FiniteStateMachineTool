#ifndef STATEACTIONDIALOG_H
#define STATEACTIONDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

#include "code.h"

namespace Ui {
class StateActionDialog;
}

class StateActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StateActionDialog(QWidget *parent = nullptr);
    StateActionDialog(int st, int act);
    ~StateActionDialog();
    void setStateAndAction(int st, int act);

private slots:
    void on_pushButton_3_clicked();
    void onTableBtnClicked();
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    
private:
    Ui::StateActionDialog *ui;
    int stateNum;
    int actionNum;
    QStandardItemModel *tableModel;
    Code file;
};

#endif // STATEACTIONDIALOG_H
