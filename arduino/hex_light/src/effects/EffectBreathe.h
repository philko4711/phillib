#ifndef PHILLIB_ARDUINO_EFFECTBREATHE_H_
#define PHILLIB_ARDUINO_EFFECTBREATHE_H_


#include "IEffect.h"
#include <Arduino.h>
#include <inttypes.h>

namespace phillib
{
namespace arduino
{
  class EffectBreathe : public IEffect
  {
    public:
      EffectBreathe(const unsigned long timeOutChange = 10);
      virtual ~EffectBreathe(){}
      virtual void process(Adafruit_NeoPixel& strip)override;
    private:
      bool _dir = false;
      unsigned long _last = millis();
      unsigned long _timeOutChange;  
      uint8_t _brightness = 255;  
};
}
}
#endif

