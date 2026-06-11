#ifndef PHILLIB_ARDUINO_EFFECTWANDERINGPXL_H_
#define PHILLIB_ARDUINO_EFFECTWANDERINGPXL_H_


#include "EffectBase.h"
#include <vector>

namespace phillib
{
namespace arduino
{
  class EffectWanderingPxl : public EffectBase
  {
    public:
      EffectWanderingPxl(const unsigned long timeOutChange = 10);
      virtual ~EffectWanderingPxl(){}
      virtual void process(CRGB* strip)override;
      virtual TypeEffect type(void)const override{return TypeEffect::WANDERING_PXL;}
      virtual String typeString(void)const override{return String("wandering_pixel");}
    private:
      std::vector<unsigned int> _pxlBuffer;
      std::vector<unsigned int>::const_iterator _current;
      
};
}
}
#endif

