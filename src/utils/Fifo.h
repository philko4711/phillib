#ifndef FIFO_H_
#define FIFO_H_

#include <deque>

namespace phillib
{
  
namespace utils
{
  



template <typename T> class Fifo
{
public:
  Fifo(const unsigned int size);
  virtual ~Fifo() {}
  const unsigned int add(const T& val);
  const unsigned int size(void) const { return _buffer.size(); }
  const T& operator[](const unsigned int i)const{return _buffer[i];}
private:
  unsigned int  _size;
  std::deque<T> _buffer;
};

template<typename T> Fifo<T>::Fifo(const unsigned int size)
    : _size(size)
{
}

template<typename T> const unsigned int Fifo<T>::add(const T& val)
{
  _buffer.push_back(val);
  if(_buffer.size() >= _size)
    _buffer.pop_front();
  return _buffer.size();  

}

} // namespace phillib

} // namespace utils


#endif