#include "minerui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MinerUI w;
    w.show();
    

    return a.exec();
}
