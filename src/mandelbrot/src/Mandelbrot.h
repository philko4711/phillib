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
    Q_OBJECT
    public:
    Mandelbrot();
    virtual ~Mandelbrot(){}
    void drawMandelbrotSet();
    public slots:
      void magnify(const QPoint& deltaCenter, const QPoint& deltaMagnify);
      void magnify(const QRect& region);
    private:
      void createPalette(const unsigned int iterationsMax);
      MainWindow _gui;
      std::vector<QColor> _palette;
      QPointF _center;
      double           _res;
      int _threshIterations;
      std::vector<uint8_t>   _rgbBuf;
};
}
}
#endif

