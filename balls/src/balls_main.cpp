#include <iostream>
#include <QtWidgets/QApplication>
#include <QtCore/qglobal.h>

#include "BallsMain.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    //phillib::BallsMain balls(100);
    phillib::BallsMain balls(0);
    balls.addBall(QPointF(10.0f, 300.0f), QPointF(2.0f, 0.0f));
    balls.addBall(QPointF(400.0f, 295.0f), QPointF(-2.0f, 0.0f), 10.0f, 25.0f, Qt::red);
    return app.exec();
}
