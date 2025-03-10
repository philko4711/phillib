#include "EffectExpand.h"
#include "LedStrip.h"
#include <Adafruit_NeoPixel.h>
#include <cmath>


namespace phillib
{
namespace arduino
{
EffectExpand::EffectExpand(const unsigned long timeOutChange):EffectBase(timeOutChange)
  {
    //_frontierOuter = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    //_frontierInner = {12, 13, 14, 15, 16, 17};
    _dir = true;
    _frontierOuter = LedStrip::halo();//{0,  1,  2,  3, 23, 24, 25, 47, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 27, 28, 29, 18,  19, 20, 21, 5, 6, 7, 8, 9, 10, 11};
    _frontierInner = LedStrip::inner();//{4, 12, 13, 14, 15, 16, 17, 22, 26, 30, 31, 32, 33, 34, 35, 46, 49, 50, 51, 52 ,53, 54};
  }

  void EffectExpand::process(Adafruit_NeoPixel& strip)
  {
    if(millis() - _last < _timeOutChange)
      return;
    //Serial.println(millis() - _last);  
  // float elapsedSince = static_cast<float>((millis() - start)) / 1000.0f;
  // auto sinF = std::sin(elapsedSince *  ((2.0f * M_PI) /  6.0f));
  // if(std::abs(sinF) < 0.1)
  //   this->switchState();
  //_brightness = static_cast<uint8_t>(std::round(std::abs(255.0f * sinF   )));    //255.0f * 2.0f * 0.005f     static_cast<float>((start - millis()) * 1000) * ((2.0f * M_PI) / (2.0f)
  
    // if(_current == States::INNER_FALLING)
    //   _current = States::INNER_RISING;
    // else if(_current == States::OUTER_FALLING)
    //   _current = States::INNER_FALLING;
    if(_dir)
    {
      bool switchState = false;
      if(++_brightness == 255)
      {
        switchState = true;
      }

      if(_current == States::INNER_RISING)  //0..255
      {
        //Serial.println("Inner Rising");
        _brightnessInner = _brightness;
        if(switchState)
        {
          _current = States::OUTER_RISING;
        }
      }
      else if(_current == States::OUTER_RISING)
      {
        //Serial.println("Outer Rising");
        _brightnessOuter = _brightness;
        if(switchState)
        {
          _current = States::OUTER_FALLING;
          _dir = false;
        }
      }
    }
    else
    {
      bool switchState = false;
      if(--_brightness == 0)
      {
        switchState = true;
      }
      if(_current == States::OUTER_FALLING)
      {
       // Serial.println("outer Falling");
        _brightnessOuter = _brightness;
        if(switchState)
        {
          _current = States::INNER_FALLING;
        }
      }  
      else if(_current == States::INNER_FALLING)
      {
        //Serial.println("Inner Falling");
        _brightnessInner = _brightness;
        if(switchState)
        {
          _current = States::INNER_RISING;
          _dir = true;
        }
      }
    }
    // Serial.println(_brightness);
    // Serial.println(_brightnessInner);
    // Serial.println(_brightnessOuter);
  
    for(auto& iter : _frontierInner)
      strip.setPixelColor(iter, _brightnessInner, 0, 0);
  
    for(auto& iter : _frontierOuter)
        strip.setPixelColor(iter, _brightnessOuter, 0, 0);
        
  strip.show();
  _last = millis();
  }  

  void EffectExpand::switchState()
  {
    switch(_current)
    {
      case(States::INNER_RISING):
        _current = States::OUTER_RISING;
        break;
      case(States::OUTER_RISING):
        _current = States::OUTER_FALLING;
        break;
      case(States::OUTER_FALLING):
        _current = States::INNER_RISING;
        break;
      default:
        Serial.println("ERROR_SWITCH");
        break;      
    }
  }

}
}
