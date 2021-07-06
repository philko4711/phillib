#include "Mandelbrot.h"
#include <iostream>
#include <phillib_utils/Complex.h>
#include <phillib_utils/random.h>
#include <vector>
#include <QtCore/QDebug>

namespace phillib
{
namespace qt
{
Mandelbrot::Mandelbrot()
{
  _gui.resize(800, 800);
  _gui.show();
  connect(&_gui, SIGNAL(magnify(const QPoint&, const QPoint&)), this, SLOT(magnify(const QPoint&, const QPoint&)));
  connect(&_gui, SIGNAL(magnify(const QRect&)), this, SLOT(magnify(const QRect&)));
  _res          = 4.0 / static_cast<double>(_gui.rect().width());
  _center = QPointF(static_cast<double>(_gui.rect().width() / 2) * _res, static_cast<double>(_gui.rect().height() / 2) * _res);
  _threshIterations = 100;
  this->createPalette(_threshIterations);
  _rgbBuf.resize(_gui.rect().width() * _gui.rect().height() * 3, 255);
}

void Mandelbrot::drawMandelbrotSet()
{
  QRect                  sizeDisplay = _gui.rect();
  
  for(int i = 0; i < sizeDisplay.height(); i++)
  {
    for(int j = 0; j < sizeDisplay.width(); j++)
    {
      double               real = static_cast<double>(j) * _res - _center.x();
      double               im   = static_cast<double>(i) * _res - _center.y();
      const utils::Complex c(real, im);
      utils::Complex       z_n(0.0, 0.0);
      int                  ctr = 0;
      for(int k = 0; k < _threshIterations; k++, ctr++)
      {
        z_n = z_n * z_n + c;
        if(z_n.abs() > 2.0)
          break;
      }
      uint8_t r = 0;
      uint8_t g = 0;
      uint8_t b = 0;
      const QColor color = _palette[ctr];
      r                  = color.red();
      g                  = color.green();
      b                  = color.blue();
      
      const int idx       = i * sizeDisplay.width() + j;
      _rgbBuf[3 * idx + 0] = r;
      _rgbBuf[3 * idx + 1] = g;
      _rgbBuf[3 * idx + 2] = b; 
    }
  }
  QImage image(_rgbBuf.data(), sizeDisplay.width(), sizeDisplay.height(), QImage::Format_RGB888);
  _gui.drawImage(image);
  _gui.update();
}

void Mandelbrot::magnify(const QPoint& deltaCenter, const QPoint& deltaMagnify)
{
  _center = _center - QPointF(static_cast<double>(deltaCenter.x()) * _res, static_cast<double>(deltaCenter.y()) * _res);//QPointF deltaReal = _center
  if(deltaMagnify.y() > 0)
  _res /= 2.0;
  else
    _res *= 2.0;
  this->drawMandelbrotSet();
}

void Mandelbrot::createPalette(const unsigned int iterationsMax)
{
  // const unsigned int n = static_cast<unsigned int>(std::ceil(static_cast<double>(iterationsMax) / 3.0));
  std::vector<int> r;
  std::vector<int> g;
  std::vector<int> b;
  phillib::utils::randomInts(iterationsMax, r, 0, 255);
  phillib::utils::randomInts(iterationsMax, g, 0, 255);
  phillib::utils::randomInts(iterationsMax, b, 0, 255);
  for(unsigned int i = 0; i < iterationsMax; i++)
  {
    _palette.push_back(QColor(r[i], g[i], b[i]));
  }
  std::cout << __PRETTY_FUNCTION__ << " created random palette with " << _palette.size() << " entries for " << iterationsMax << " iterations" << std::endl;
}

void Mandelbrot::magnify(const QRect& region)
{
  qDebug() << __PRETTY_FUNCTION__ << "";
  QRect regionQuad = region;
  regionQuad.setWidth(regionQuad.height());
  QPointF centerNew = static_cast<QPointF>(regionQuad.center()) * _res - _center;
  qDebug() << __PRETTY_FUNCTION__ << "centernew " << centerNew;
}

} // namespace qt
} // namespace phillib
