#include "wizarddialog.h"
#include "ui_wizarddialog.h"
#include "stateactiondialog.h"
#include <QMessageBox>
#include <stack>

using namespace std;
stack<QDialog *> gDlgStack;
WizardDialog::WizardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WizardDialog)
{
    ui->setupUi(this);
    numState = 0;
    numAction = 0;
}

WizardDialog::~WizardDialog()
{
    delete ui;
}

void WizardDialog::on_pushButton_clicked()
{
    //获取动作和状态的个数
    QString  stateStr = ui->lineEdit_state->text();
    QString  actionStr = ui->lineEdit_action->text();
    if(stateStr.isNull() || actionStr.isNull())
    {
        QMessageBox::information(NULL, "提示", "动作和状态不能为空");
        return ;
    }
    numState = stateStr.toInt();
    numAction = actionStr.toInt();
    if(numState == 0 || numAction == 0)
    {
        QMessageBox::information(NULL, "提示", "动作和状态不能为0");
        return ;
    }
    StateActionDialog *pnextDlg = new StateActionDialog(numState, numAction);
    this->hide();
    gDlgStack.push(this);
    pnextDlg->show();
}


