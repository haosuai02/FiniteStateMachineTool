#include "mainwindow.h"
#include "wizarddialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WizardDialog w;
    w.exec();
//    MainWindow w;
//    w.show();
    return a.exec();
}
