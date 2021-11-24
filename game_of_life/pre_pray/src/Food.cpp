#include "Food.h"
#include <cmath>
#include <QtCore/QDebug>

namespace phillib
{
namespace game_of_life
{
Food::Food()_amount(10), _amountInitial(10.0f) 
  {
    //qDebug() << __PRETTY_FUNCTION__ << "new food " << pos;
  }

unsigned int Food::wither(const unsigned int nFreeNeighbours)
{
  qDebug() << __PRETTY_FUNCTION__ << "";
   unsigned int subs = 9 - nFreeNeighbours;
   if(subs > _amount)
    _amount = 0;
  else  
    _amount -= subs;
  return _amount;
}

uint8_t Food::health(void)const
{
  qDebug() << __PRETTY_FUNCTION__ << "";
  float amount = static_cast<float>(_amount); 
  return static_cast<uint8_t>(std::round((amount / _amountInitial) * 100.0f));
  }
}
}
