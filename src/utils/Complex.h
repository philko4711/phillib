#ifndef PHILLIB_UTILS_COMPLEX_H_
#define PHILLIB_UTILS_COMPLEX_H_

#include <cmath>

namespace phillib
{
namespace utils
{
class Complex
{
public:
  Complex(const double r, const double i);
  virtual ~Complex() {}
  const double   abs() const { return std::sqrt(_r * _r + _i * _i); }
  const Complex& operator+=(const Complex& var);
  Complex operator+(const Complex& var)const{return Complex(_r + var._r, _i + var._i);}
  const Complex& operator*=(const Complex& var);
  Complex operator*(const Complex& var)const;//{return Complex(_r * var._r, _i * var._i);}
private:
  double _r = 0.0;
  double _i = 0.0;
};
} // namespace utils
} // namespace phillib
#endif
