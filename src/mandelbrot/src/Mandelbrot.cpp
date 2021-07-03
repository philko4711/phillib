#include "Mandelbrot.h"
#include <vector>
#include <phillib_utils/Complex.h>
#include <iostream>

namespace phillib
{
Mandelbrot::Mandelbrot()
  {
    _gui.resize(800, 800);
    _gui.show();
  }

void Mandelbrot::drawMandelbrotSet()
{
  QRect sizeDisplay = _gui.rect();
  QVector<qt::QPointRGB> pxlsMandelbrot;
  std::vector<uint8_t> rgbBuf(sizeDisplay.width() * sizeDisplay.height() * 3, 255);
  const double res =  4.0 / static_cast<double>(sizeDisplay.width());
  const int iterationMax = 255 * 3;
  //unsigned int ctr = 0;
  for (int i = 0; i < sizeDisplay.height(); i++)
  {
    for (int j = 0; j < sizeDisplay.width(); j++)
    {
      //std::cout << __PRETTY_FUNCTION__ << " i j " << i << " " << j << std::endl;
      double real = static_cast<double>(j) * res -2.0;
      double im = static_cast<double>(i) * res -2.0;
      const utils::Complex c(real, im);
      utils::Complex z_n(0.0, 0.0);
      int ctr = 0;
      for(int k = 0; k < iterationMax; k++)
      {
        z_n = z_n * z_n + c;
        if(z_n.abs() > 2.0)
          break;  
      }
      if(ctr >= iterationMax - 1)
        continue;
      uint8_t r = 0;
      uint8_t g = 0;
      uint8_t b = 0;
      if(ctr < 255)
      {
        r = ctr;
      }  
      else if (ctr < 2 * 255)
      {
        r = 255;
        g = ctr - 255;
        b = 0;
      }
      else
      {
        r = 255;
        g = 255;
        b = ctr -  2 * 255;
      }
      const int idx = i * sizeDisplay.width() + j;
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


}
