#ifndef PHILLIB_ARDUINO_IEFFECT_H_
#define PHILLIB_ARDUINO_IEFFECT_H_

#include <Arduino.h>

struct CRGB;
//class Adafruit_NeoPixel;

namespace phillib
{
namespace arduino
{
  class IEffect
  {
    public:
      enum class TypeEffect
      {
        BREATHE = 0,
        EXPAND,
        WANDERING_PXL,
        PACIFICA,
        ERROR
      };
      IEffect(){}
      virtual ~IEffect(){}
      virtual void process(CRGB* strip) = 0;
      virtual TypeEffect type(void)const = 0;
      virtual String typeString(void)const = 0;
      virtual IEffect::TypeEffect stringToTypeEffect(const String& effect) = 0;
};
}
}
#endif

