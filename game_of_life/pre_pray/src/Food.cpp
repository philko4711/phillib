#include "Food.h"
#include <cmath>
#include <QtCore/QDebug>
#include <QtGui/QPainter>

namespace phillib
{
namespace game_of_life
{
Food::Food():_amount(10), _amountInitial(10.0f), _graphic(new GraphicItemFood)  //const QPointF& pos
  {
    _graphic->setColor(Qt::green);
    //QGraphicsItem::set
    //this->setPos(pos.x(), pos.y());
  }

unsigned int Food::wither(const unsigned int nFreeNeighbours)
{
   unsigned int subs = 9 - nFreeNeighbours;
   if(subs > _amount)
    _amount = 0;
  else  
    _amount -= subs;
  QColor color(Qt::green);
  float amount = static_cast<float>(_amount); 
  color.setAlphaF(amount / _amountInitial);  
  _graphic->setColor(color);
  return _amount;
}

uint8_t Food::health(void)const
{
  float amount = static_cast<float>(_amount); 
  return static_cast<uint8_t>(std::round((amount / _amountInitial) * 100.0f));
  }

// void Food::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
// {
//   qDebug() << __PRETTY_FUNCTION__ << "";
//   painter->save();
//   QPen pen(Qt::SolidLine);
//   QBrush brush(Qt::SolidPattern);
//   QColor color(Qt::green);
//   float amount = static_cast<float>(_amount);
  
//   color.setAlphaF((amount / _amountInitial));
//   pen.setColor(color);
//   brush.setColor(color);
// painter->setPen(pen);  
// painter->setBrush(brush);
// painter->drawRect(this->boundingRect());
//   painter->restore();
// }

void Food::setIdx(const QPoint& idx)
{
_cellIdx = idx;
_graphic->setPos(idx * 10);// + QPointF(5.0, 5.0));   //toDo: the map cell resolution must be used
}

}
}
