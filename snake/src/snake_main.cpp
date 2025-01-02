#include <iostream>
#include <QtWidgets/QApplication>

#include "Snake.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    phillib::Snake snake;
    return app.exec();
}
