#ifndef CHOOSEPATHDIALOG_H
#define CHOOSEPATHDIALOG_H

#include <QDialog>
#include <code.h>
#include <QString>

namespace Ui {
class ChoosePathDialog;
}

class ChoosePathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoosePathDialog(QWidget *parent = nullptr);
    ChoosePathDialog(Code &thFile, QWidget *parent = nullptr);
    ~ChoosePathDialog();
    Code file;
    QString filePath;
private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ChoosePathDialog *ui;
};

#endif // CHOOSEPATHDIALOG_H
