#include <iostream>
#include <QtWidgets/QApplication>

#include "BallsMain.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    phillib::BallsMain balls(1);
    balls.addBall(QPointF(400.0f, 300.0f), QPointF(1.1f, -11.1f));
    balls.addBall(QPointF(400.0f, 300.0f), QPointF(11.1f, 1.1f));
    return app.exec();
}
