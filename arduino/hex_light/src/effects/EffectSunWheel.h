#ifndef PHILLIB_ARDUINO_EFFECTSUNWHEEL_H_
#define PHILLIB_ARDUINO_EFFECTSUNWHEEL_H_


#include "EffectBase.h"
#include <memory>
#include <FastLED.h>

namespace phillib
{
namespace arduino
{
  class EffectSunWheel : public EffectBase
  {
    public:
    EffectSunWheel(const unsigned long timeOutChange = 10);
    virtual ~EffectSunWheel(){}
    virtual void process(CRGB* strip)override;
    private:
      std::vector<uint8_t> _idcs0;
      std::vector<uint8_t> _idcs1;
      std::vector<uint8_t>* _current = nullptr;
      std::vector<float> _innerSin;
      unsigned long _start;
};
}
}
#endif

