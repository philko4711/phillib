#ifndef PHILLIB_MANDELBROT_H_
#define PHILLIB_MANDELBROT_H_

#include <QtCore/QObject>
#include <phillib_qt/WidgetImage.h>
namespace phillib
{
  class Mandelbrot : public QObject
  {
    public:
    Mandelbrot();
    virtual ~Mandelbrot(){}
    void drawMandelbrotSet();
    private:
      phillib::qt::WidgetImage _gui;
};
}
#endif

