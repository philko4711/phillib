#ifndef PHILLIB_BALL_H_
#define PHILLIB_BALL_H_

#include <QtWidgets/QGraphicsEllipseItem>

namespace phillib
{
  class Ball
  {
  public:
    Ball(const QPointF &pos, const QPointF &v);
    virtual ~Ball() {}
    QGraphicsEllipseItem& itemGraphic(void) { return _itemGraphic; }
    void iterate();
    const QPointF& v(void)const{return _v;}
    void setV(const QPointF& v){_v = v;}
    void setPos(const QPointF& pos){_itemGraphic.setPos(pos);}
  private:
    QGraphicsEllipseItem _itemGraphic;
    QPointF _v;
  };
}
#endif
