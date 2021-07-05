#include <QtWidgets/QApplication>
#include "Mandelbrot.h"
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    phillib::qt::Mandelbrot mandelbrot;
    mandelbrot.drawMandelbrotSet();
    return app.exec();
}
