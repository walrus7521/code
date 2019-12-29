#include "alfa147gta.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Alfa147gta w;
    w.show();

    return a.exec();
}
