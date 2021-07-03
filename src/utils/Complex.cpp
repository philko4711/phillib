#include "Complex.h"

namespace phillib
{
namespace utils
{
Complex::Complex(const double r, const double i):_r(r), _i(i)
  {
  }
const Complex& Complex::operator+=(const Complex& var){
  _i = _i + var._i;
  _r = _r + var._r;
  return *this;
}
const Complex& Complex::operator*=(const Complex& var){
  _i = _i * var._i;
  _r = _r * var._r;
  return *this;
}

// Complex Complex::operator+(const Complex& var)
// {
//   return Complex(_r + var._r, _i + var._i);
// }
 Complex Complex::operator*(const Complex& var)const
{
  double r = _r * var._r - _i * var._i;
  double i = _r * var._i + _i * var._r;
  return Complex(r, i);
}

}
}
