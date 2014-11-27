#include "JudoMasterMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JudoMasterMainWindow w;
    w.show();

    return a.exec();
}
