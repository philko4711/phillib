#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include "FractalLab.h"
#include "fractals/FractalTree.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    phillib::FractalLab::instance().show();
    phillib::FractalTree tree(QLineF(QPointF(0.0f, -100.0f), QPointF(0.0f, 100.0f)));
    phillib::FractalLab::instance().setTree(&tree);
    
    //lab.show();
    return app.exec();
}
