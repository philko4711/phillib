#include <QtWidgets/QApplication>
#include "PredPray.h"

int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    phillib::game_of_life::PredPray simulator;
    return app.exec();
    return 0;
}