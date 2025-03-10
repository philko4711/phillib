#include "EffectBreathe.h"

#include <Adafruit_NeoPixel.h>

namespace phillib
{
namespace arduino
{
EffectBreathe::EffectBreathe(const unsigned long timeOutChange):EffectBase(timeOutChange)
  {
  }

void EffectBreathe::process(Adafruit_NeoPixel& strip)
{
  if(millis() - _last >= _timeOutChange)
  {
    _last = millis();
    if(_dir == true)
    {
      if(++_brightness >= 255)
        _dir = false;
    }
    else
    {
      if(--_brightness <= 1)
        _dir = true;
    }
  }
  strip.setBrightness(_brightness);
  strip.show();
}

}
}
