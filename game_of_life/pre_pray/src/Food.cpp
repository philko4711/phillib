#include "Food.h"

namespace phillib
{
namespace game_of_life
{
Food::Food(const QPoint& pos):ObjectMap(pos),_amount(100)
  {
  }

void Food::wither()
{
  _amount--;
}
}
}
