#ifndef PHILLIB_ARDUINO_IEFFECT_H_
#define PHILLIB_ARDUINO_IEFFECT_H_

class Adafruit_NeoPixel;

namespace phillib
{
namespace arduino
{
  class IEffect
  {
    public:
      IEffect(){}
      virtual ~IEffect(){}
      virtual void process(Adafruit_NeoPixel& strip) = 0;
};
}
}
#endif

