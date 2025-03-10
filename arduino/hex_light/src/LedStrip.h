#ifndef PHILLIB_ARDUINO_LEDSTRIP_H_
#define PHILLIB_ARDUINO_LEDSTRIP_H_

#include <vector>
#include <inttypes.h>

namespace phillib
{
namespace arduino
{
  class LedStrip
  {
    public:
    LedStrip(){}
    virtual ~LedStrip(){}
    static const std::vector<uint8_t> halo(void){return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};}
    static const std::vector<uint8_t> inner(void){return {12, 13, 14, 15, 16, 17};}
    //const std::vector<uint8_t> panel(const uint8_t)const;
};
}
}
#endif

