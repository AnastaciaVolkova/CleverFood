#include "mainwindow.h"

#include <QApplication>

#include "controller.hpp"
#include "model.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    MainWindow w(&controller);
    Model model(&controller);
    controller.SetView(&w);
    controller.SetModel(&model);
    w.show();
    return a.exec();
}
