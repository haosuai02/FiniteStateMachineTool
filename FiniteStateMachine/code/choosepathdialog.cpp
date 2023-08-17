#include "choosepathdialog.h"
#include "ui_choosepathdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <stateactiondialog.h>

#include <stack>

using namespace  std;
extern stack<QDialog *> gDlgStack;
ChoosePathDialog::ChoosePathDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoosePathDialog)
{
    ui->setupUi(this);
}
ChoosePathDialog::ChoosePathDialog(Code &thFile,QWidget *parent):
    QDialog(parent),
    ui(new Ui::ChoosePathDialog)
{
    ui->setupUi(this);
    file = thFile;
}
ChoosePathDialog::~ChoosePathDialog()
{
    delete ui;
}

void ChoosePathDialog::on_pushButton_clicked()
{
    if(filePath.isNull())
    {
        QMessageBox::information(NULL, "提示", "请选择要生成的路径");
        return ;
    }
    int res = file.createHeadFile(filePath.toStdString());
    if(res < 0)
    {
        QMessageBox::information(NULL, "提示", "创建文件失败");
        return ;
    }
    res = file.createCppFile(filePath.toStdString());
    if(res < 0)
    {
        QMessageBox::information(NULL, "提示", "创建文件失败");
        return ;
    }
    QMessageBox::information(NULL, "提示", "创建文件成功");
}

//选择路径
void ChoosePathDialog::on_pushButton_3_clicked()
{
    filePath = QFileDialog::getExistingDirectory(this,  tr("Open File"), NULL);
    ui->lineEdit->setText(filePath);
}

void ChoosePathDialog::on_pushButton_2_clicked()
{
    StateActionDialog *pbefor = (StateActionDialog *)gDlgStack.top();
    this->close();
    gDlgStack.pop();
    pbefor->show();
}
