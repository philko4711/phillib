#include <iostream>
#include <QtWidgets/QApplication>

#include "gui/BallsMainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    phillib::BallsMainWindow gui(800, 600);
    gui.show();
    return app.exec();
}
