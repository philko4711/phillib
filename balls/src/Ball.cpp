#include "Ball.h"
#include <QtGui/QPen>
#include <QtGui/QBrush>

namespace phillib
{
Ball::Ball(const QPointF& pos, const QPointF& v):_v(v)
  {
    _itemGraphic.setRect(0.0f, 0.0f, 5.0f, 5.0f);   //TODO: make adjustable
    QBrush brush(Qt::SolidPattern);
    QPen pen(Qt::SolidLine);
    pen.setWidth(1);
    pen.setColor(Qt::green);
    brush.setColor(Qt::green);
    _itemGraphic.setBrush(brush);
    _itemGraphic.setPen(pen);
    //_itemGraphic.setVisible(true);
    _itemGraphic.setPos(pos.x(), pos.y());
  }

  void Ball::iterate()
  {
    QPointF pos = _itemGraphic.pos();
    pos += _v;
    _itemGraphic.setPos(pos);
  }

}
