#include "EffectSunWheel.h"
#include "LedStrip.h"
namespace phillib
{
namespace arduino
{
  EffectSunWheel::EffectSunWheel(const unsigned long timeOutChange):EffectBase(timeOutChange),_start(millis())
  {
    auto halo = LedStrip::halo();
    for(unsigned int i = 0; i < halo.size(); i += 2)
    {
        _idcs0.push_back(halo[i]);
        Serial.print(halo[i]);
        Serial.print("  ");
    }
    Serial.print("\n");
    //_current = &_idcs0;
    _brightness = 0;
    _dir = true;
    for(unsigned int i = 0;  i < LedStrip::inner().size(); i++)
      _innerSin.push_back(static_cast<float>(random(3.0f, 5.0f)));
  }

  void EffectSunWheel::process(CRGB* strip)
  {
    static bool dirLast = _dir;
    
    // float elapsedSince = static_cast<float>((millis() - _start)) / 1000.0f;
    
    // for(unsigned int i = 0; i < LedStrip::inner().size(); i++)
    // {
    //   auto sinF = std::abs(std::sin(elapsedSince *  ((2.0f * M_PI) /  6.0f) + _innerSin[i]));
    //   strip.setPixelColor(LedStrip::inner()[i], static_cast<uint8_t>(std::floor(sinF * 255.0f)), 0, 0);
    // }
    if(millis() - _last >= _timeOutChange)
    {
      _last = millis();
      if(_dir == true)
      {
        if(++_brightness >= 255)
          _dir = false;
      }
      else
      {
        if(--_brightness < 1)
        {
          _dir = true;
        }
      }
    }
    if(_dir && !dirLast)
    {
      for(auto& iter : _idcs0)
      {
        if(++iter >= LedStrip::halo().back())
        {
          iter = LedStrip::halo().back() - iter;     
        }
        Serial.print(iter);
        Serial.print("  ");
      }
      Serial.print("\n");
      for(auto& iter : LedStrip::halo())
        strip[iter].setRGB( 0, 0, 0);  
        
      // if(*_current == _idcs0)
      // {
      //   _current = &_idcs1;
      //   for(auto& iter : _idcs0)
      //     strip.setPixelColor(iter, 0, 0, 0);  
      // }
      // else
      // {
      //   _current = &_idcs0;  
      //   for(auto& iter : _idcs1)
      //     strip.setPixelColor(iter, 0, 0, 0);  
      // }
    }
    for(auto& iter : _idcs0)
      strip[iter].setRGB(_brightness, 0, 0);
    FastLED.show();
    dirLast = _dir;
  }

}
}
