#include "Food.h"
#include <cmath>
#include <QtCore/QDebug>

namespace phillib
{
namespace game_of_life
{
Food::Food(const QPoint& pos):ObjectMap(pos),_amount(100)
  {
    qDebug() << __PRETTY_FUNCTION__ << "new food " << pos;
  }

unsigned int Food::wither()
{
  return --_amount;
}

uint8_t Food::health(void)const
{
  float amount = static_cast<float>(_amount);
  return static_cast<uint8_t>(std::round((amount / 100.0f) * 100.0f));
  }
}
}
