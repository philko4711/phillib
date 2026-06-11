#include "EffectBreathe.h"

#include <FastLED.h>

namespace phillib
{
namespace arduino
{
EffectBreathe::EffectBreathe(const unsigned long timeOutChange):EffectBase(timeOutChange)
  {
    Serial.println(__PRETTY_FUNCTION__);
  }

void EffectBreathe::process(CRGB* strip)
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
  FastLED.setBrightness(_brightness);
  FastLED.show();
}

}
}
