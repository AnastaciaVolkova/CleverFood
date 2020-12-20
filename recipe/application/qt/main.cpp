#include "qtview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTView w(&a);
    w.show();
    return a.exec();
}
