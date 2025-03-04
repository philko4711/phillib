#ifndef PHILLIB_ARDUINO_EFFECTEXPAND_H_
#define PHILLIB_ARDUINO_EFFECTEXPAND_H_


#include "EffectBase.h"

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
      virtual void process(Adafruit_NeoPixel& strip)override;
    private:
      void switchState();
      std::vector<uint8_t> _frontierOuter;
      std::vector<uint8_t> _frontierInner;
      uint8_t _brightnessOuter = 0;
      uint8_t _brightnessInner = 0;
      States _current = States::INNER_RISING;
};
}
}
#endif

