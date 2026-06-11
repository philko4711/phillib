#ifndef PHILLIB_ARDUINO_EFFECTBASE_H_
#define PHILLIB_ARDUINO_EFFECTBASE_H_


#include "IEffect.h"
#include <inttypes.h>
#include <Arduino.h>
namespace phillib
{
namespace arduino
{
  class EffectBase : public IEffect
  {
    public:
    EffectBase(const unsigned long timeOutChange = 10):_timeOutChange(timeOutChange){}
    virtual ~EffectBase(){}
    virtual IEffect::TypeEffect stringToTypeEffect(const String& effect)override;
    protected:
      unsigned long _last = millis();
      unsigned long _timeOutChange;  
      uint8_t _brightness = 255;  
      bool _dir = false;
};
}
}
#endif

