
#include "EffectWanderingPxl.h"
#include <FastLED.h>
#include <iostream>
namespace phillib
{
namespace arduino
{
EffectWanderingPxl::EffectWanderingPxl(const unsigned long timeOutChange):EffectBase(timeOutChange)
  {
    Serial.println(__PRETTY_FUNCTION__);
    //_pxlBuffer = {0, 1, 2, 3, 23, 24, 25, 47, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 27, 28, 29, 18, 19, 20, 21, 5, 6, 7, 8, 9, 10, 11};
    _pxlBuffer = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    _current = _pxlBuffer.begin();
    _brightness = 0;
    _dir = true;
  }

void EffectWanderingPxl::process(CRGB* strip)
{
  // const unsigned int idxCur = *_current;
  // unsigned int idxNext = 0;
  // if(_current + 1 < _pxlBuffer.end())
  //   idxNext = *(_current + 1); 
  // else
  //   idxNext = *_pxlBuffer.begin();
  // if(_dir) 
  // { 
  //   if(_brightness >= 255)
  //   {
  //     _brightness = 255;
  //     _dir = false;
  //     if(++_current == _pxlBuffer.end())
  //       _current = _pxlBuffer.begin();
  //   }
  //   else
  //     _brightness++;
  //   strip.setPixelColor(idxCur, _brightness, 0, 0);
  //   strip.setPixelColor(idxNext, 255 - _brightness, 0, 0);
  // }
  // else
  // {
  //   if(_brightness >= 1)  
  //     _brightness--;   
  //   else
  //   {
  //     _brightness = 0; 
  //     _dir = true; 
  //     if(++_current == _pxlBuffer.end())
  //       _current = _pxlBuffer.begin();
  //   }
  //   strip.setPixelColor(idxCur, 255 - _brightness, 0, 0);
  //   strip.setPixelColor(idxNext, _brightness, 0, 0);
  // }
  // strip.show();
}

}
}
