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
    static const std::vector<uint8_t> halo(void){return {0,  1,  2,  3, 23, 24, 25, 47, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 27, 28, 29, 18,  19, 20, 21, 5, 6, 7, 8, 9, 10, 11};} 
    static const std::vector<uint8_t> inner(void){return {4, 12, 13, 14, 15, 16, 17, 22, 26, 30, 31, 32, 33, 34, 35, 46, 49, 50, 51, 52 ,53, 54};} 
    static const std::vector<uint8_t> haloDebug(void){return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};}
    static const std::vector<uint8_t> innerDebug(void){return {12, 13, 14, 15, 16, 17};}
    //const std::vector<uint8_t> panel(const uint8_t)const;
};
}
}
#endif

