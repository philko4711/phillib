
#include "EffectWanderingPxl.h"
#include <Adafruit_NeoPixel.h>
#include <iostream>
namespace phillib
{
namespace arduino
{
EffectWanderingPxl::EffectWanderingPxl(const unsigned long timeOutChange):EffectBase(timeOutChange)
  {
    _pxlBuffer = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    _current = _pxlBuffer.begin();
    _brightness = 0;
    _dir = true;
  }

void EffectWanderingPxl::process(Adafruit_NeoPixel& strip)
{
  const unsigned int idxCur = *_current;
  unsigned int idxNext = 0;
  if(_current + 1 < _pxlBuffer.end())
    idxNext = *(_current + 1); 
  else
    idxNext = *_pxlBuffer.begin();
  if(_dir) 
  { 
    if(_brightness >= 255)
    {
      _brightness = 255;
      _dir = false;
      if(++_current == _pxlBuffer.end())
        _current = _pxlBuffer.begin();
    }
    else
      _brightness++;
    strip.setPixelColor(idxCur, _brightness, _brightness, _brightness);
    strip.setPixelColor(idxNext, 255 - _brightness, 255 - _brightness, 255 - _brightness);
  }
  else
  {
    if(_brightness >= 1)  
      _brightness--;   
    else
    {
      _brightness = 0; 
      _dir = true; 
      if(++_current == _pxlBuffer.end())
        _current = _pxlBuffer.begin();
    }
    strip.setPixelColor(idxCur, 255 - _brightness, 255 - _brightness, 255 - _brightness);
    strip.setPixelColor(idxNext, _brightness, _brightness, _brightness);
  }
  strip.show();
}

}
}
