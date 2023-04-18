#include "cookpp.h"
#include <QtWidgets/QApplication>
#include "debug.h"

int main(int argc, char *argv[])
{

    initDb(); //empty File must be create beforehand
    QApplication a(argc, argv);
    cookpp w;
    w.show();
    return a.exec();
}
