#ifndef PHILLIB_ARDUINO_EFFECTEXPAND_H_
#define PHILLIB_ARDUINO_EFFECTEXPAND_H_


#include "EffectBase.h"
#include <FastLED.h>

namespace phillib
{
namespace arduino
{
  class EffectExpand : public EffectBase
  {
    public:
      enum class States
      {
        INNER_RISING = 0,
        OUTER_RISING,
        OUTER_FALLING,
        INNER_FALLING
      };
      EffectExpand(const unsigned long timeOutChange = 10);
      virtual ~EffectExpand(){}
      virtual void process(CRGB* strip)override;
      virtual TypeEffect type(void)const override{return TypeEffect::EXPAND;}
      virtual String typeString(void)const override{return String("expand");}
    private:
      void switchState();
      std::vector<uint8_t> _frontierOuter;
      std::vector<uint8_t> _frontierInner;
      fl::u8 _brightnessOuter = 0;
      fl::u8 _brightnessInner = 0;
      States _current = States::INNER_RISING;
};
}
}
#endif

