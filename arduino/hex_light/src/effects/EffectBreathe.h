#ifndef PHILLIB_ARDUINO_EFFECTBREATHE_H_
#define PHILLIB_ARDUINO_EFFECTBREATHE_H_


#include "EffectBase.h"
#include <Arduino.h>
#include <inttypes.h>

namespace phillib
{
namespace arduino
{
  class EffectBreathe : public EffectBase
  {
    public:
      EffectBreathe(const unsigned long timeOutChange = 10);
      virtual ~EffectBreathe(){}
      virtual void process(Adafruit_NeoPixel& strip)override;
    private:
      
      // unsigned long _last = millis();
      // unsigned long _timeOutChange;  
};
}
}
#endif

