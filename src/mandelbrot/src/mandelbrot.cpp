#include <QtWidgets/QApplication>
#include "Mandelbrot.h"
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    phillib::Mandelbrot mandelbrot;
    mandelbrot.drawMandelbrotSet();
    return app.exec();
}
