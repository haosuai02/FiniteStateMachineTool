#include "stateactiondialog.h"
#include "ui_stateactiondialog.h"
#include <QDebug>
#include <code.h>
#include <stack>
#include "wizarddialog.h"
#include "choosepathdialog.h"

using namespace std;
extern stack<QDialog *> gDlgStack;
StateActionDialog::StateActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StateActionDialog)
{
    ui->setupUi(this);
}
StateActionDialog::StateActionDialog(int st, int act):
      QDialog(NULL),
      ui(new Ui::StateActionDialog)
{

    setStateAndAction(st, act);
    ui->setupUi(this);
    ui->pushButton_3->setVisible(false);
    tableModel = new QStandardItemModel();
     QStringList table_h_headers;
     QStringList table_v_headers;

    for(int i = 0;i < actionNum ;i++)
    {
        QString headerStr;
        headerStr.sprintf("动作%d", i+1);
        //tableModel->setHeaderData(i+1,Qt::Horizontal,headerStr);
        table_h_headers<<headerStr;
    }
    tableModel->setHorizontalHeaderLabels(table_h_headers);
    for(int i = 0; i < stateNum;i++)
    {
        QString headerStr;
        headerStr.sprintf("状态%d", i+1);
        //tableModel->setHeaderData(i+1,Qt::Horizontal,headerStr);
        table_v_headers<<headerStr;
    }
    tableModel->setVerticalHeaderLabels(table_v_headers);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(tableModel);

    for(int i = 0;i < stateNum;i++)
    {
        for(int j = 0;j < actionNum;j++)
        {
            QPushButton *button = new QPushButton("0");
            button->setProperty("state", i);
            button->setProperty("action", j);
            ui->tableView->setIndexWidget(tableModel->index(i,j), button);
            connect(button, SIGNAL(clicked(bool)), this, SLOT(onTableBtnClicked()));
        }
    }

}
void StateActionDialog::onTableBtnClicked()
{
    QPushButton *button = (QPushButton*)sender();
    //提取按钮的自定义属性 数据类型须统一
    int state = button->property("state").toInt();
    int action = button->property("action").toInt();

    file.fsm.fsmTable[state][action] = !file.fsm.fsmTable[state][action];
    if(file.fsm.fsmTable[state][action])
    {
        button->setText("1");
    }
    else
    {
        button->setText("0");
    }
}
void StateActionDialog::setStateAndAction(int st, int act)
{
    stateNum = st;
    actionNum = act;
    file.setStateAction(st, act);
}
StateActionDialog::~StateActionDialog()
{
    delete ui;
}

//根据状态和动作生成源代码
void StateActionDialog::on_pushButton_3_clicked()
{
    file.createHeadFile("C:\\Users\\Administrator\\Desktop\\");
    file.createCppFile("C:\\Users\\Administrator\\Desktop\\");
}

void StateActionDialog::on_pushButton_2_clicked()
{
    WizardDialog *pbefor = (WizardDialog *)gDlgStack.top();
    this->close();
    gDlgStack.pop();
    pbefor->show();
}

void StateActionDialog::on_pushButton_clicked()
{
    ChoosePathDialog *pnext = new ChoosePathDialog(file);
    gDlgStack.push(this);
    this->hide();
    pnext->show();
}
