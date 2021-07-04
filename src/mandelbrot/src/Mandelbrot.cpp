#include "Mandelbrot.h"
#include <iostream>
#include <phillib_utils/Complex.h>
#include <phillib_utils/random.h>
#include <vector>

namespace phillib
{
Mandelbrot::Mandelbrot()
{
  _gui.resize(800, 800);
  _gui.show();
}

void Mandelbrot::drawMandelbrotSet()
{
  QRect                  sizeDisplay = _gui.rect();
  QVector<qt::QPointRGB> pxlsMandelbrot;
  std::vector<uint8_t>   rgbBuf(sizeDisplay.width() * sizeDisplay.height() * 3, 255);
  const double           res          = 4.0 / static_cast<double>(sizeDisplay.width());
  const int              iterationMax = 255 * 3;
  this->createPalette(iterationMax);
  // unsigned int ctr = 0;
  for(int i = 0; i < sizeDisplay.height(); i++)
  {
    for(int j = 0; j < sizeDisplay.width(); j++)
    {
      // std::cout << __PRETTY_FUNCTION__ << " i j " << i << " " << j << std::endl;
      double               real = static_cast<double>(j) * res - 2.0;
      double               im   = static_cast<double>(i) * res - 2.0;
      const utils::Complex c(real, im);
      utils::Complex       z_n(0.0, 0.0);
      int                  ctr = 0;
      for(int k = 0; k < iterationMax; k++, ctr++)
      {
        z_n = z_n * z_n + c;
        if(z_n.abs() > 2.0)
          break;
      }
      uint8_t r = 0;
      uint8_t g = 0;
      uint8_t b = 0;
      // if(ctr < 255)
      // {
      //   r = ctr;
      //   g = 0;
      //   b = 0;
      // }
      const QColor color = _palette[ctr];
      r = color.red();
      g = color.green();
      b = color.blue();
      //else if(ctr % )
      // if(ctr == iterationMax -1)
      // {
      //   r = g = b = 0;
      // }
      // else
      // if(ctr < iterationMax)
      // {
      //   r = ctr - iterationMax;
      // }
      // else if(ctr < iterationMax + 255)
      // {
      //   r = 0;
      //   g = 0;
      //   b = ctr - iterationMax;
      // }
      // else
      // {
      //   r = 0;
      //   g = 0;
      //   b = 0;
      //}
      const int idx       = i * sizeDisplay.width() + j;
      rgbBuf[3 * idx + 0] = r;
      rgbBuf[3 * idx + 1] = g;
      rgbBuf[3 * idx + 2] = b;
      // std::cout << __PRETTY_FUNCTION__ << " i j im re " << i << " " << j << " " << real << " " << im << std::endl;
      // if(ctr >= 10)
      //   std::abort();
    }

    /* code */
  }
  QImage image(rgbBuf.data(), sizeDisplay.width(), sizeDisplay.height(), QImage::Format_RGB888);
  _gui.setImageBackground(image);
  _gui.update();
}

void Mandelbrot::createPalette(const unsigned int iterationsMax)
{
  //const unsigned int n = static_cast<unsigned int>(std::ceil(static_cast<double>(iterationsMax) / 3.0));
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

} // namespace phillib
