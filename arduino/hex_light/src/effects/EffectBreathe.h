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
      virtual void process(CRGB* strip)override;
      virtual TypeEffect type(void)const override{return TypeEffect::BREATHE;}
      virtual String typeString(void)const override{return String("breathe");}
    private:
      
      // unsigned long _last = millis();
      // unsigned long _timeOutChange;  
};
}
}
#endif

