#ifndef PHILLIB_MANDELBROT_H_
#define PHILLIB_MANDELBROT_H_

#include <QtCore/QObject>
#include <phillib_qt/WidgetImage.h>
#include "gui/MainWindow.h"
namespace phillib
{
  namespace qt
  {
  class Mandelbrot : public QObject
  {
    public:
    Mandelbrot();
    virtual ~Mandelbrot(){}
    void drawMandelbrotSet();
    private:
      void createPalette(const unsigned int iterationsMax);
      MainWindow _gui;
      std::vector<QColor> _palette;
};
}
}
#endif

