#ifndef PHILLIB_ARDUINO_EFFECTPACIFICA_H_
#define PHILLIB_ARDUINO_EFFECTPACIFICA_H_


#include "EffectBase.h"

#include <FastLED.h>
FASTLED_USING_NAMESPACE

namespace phillib
{
namespace arduino
{


  class EffectPacifica : public EffectBase
  {
    public:
      CRGBPalette16 pacificaPalette_1 = 
      { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
        0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50 };
      CRGBPalette16 pacificaPalette_2 = 
      { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
        0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F };
    CRGBPalette16 pacificaPalette_3 = 
      { 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33, 
      0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF };
      EffectPacifica(CRGB* strip, const int numLeds);
      virtual ~EffectPacifica(){}
      virtual void process(CRGB* strip)override;
      virtual IEffect::TypeEffect type(void)const override{return TypeEffect::PACIFICA;}
      virtual String typeString(void)const override{return String("pacifica");}
    private:
      void pacificaOneLayer( CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff);
      void pacificaAddWhitecaps();
      void pacificaDeepenColors();
      CRGB* const _strip;
      const int _numLeds;
};
}
}
#endif

