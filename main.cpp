#include "JudoMasterMainWindow.h"
#include "JudoMasterApplication.h"

int main(int argc, char *argv[])
{
    JudoMasterApplication a(argc, argv);
    JudoMasterMainWindow w;
    w.show();

    return a.exec();
}
