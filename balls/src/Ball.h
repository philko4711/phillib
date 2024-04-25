#ifndef PHILLIB_BALL_H_
#define PHILLIB_BALL_H_

#include <QtWidgets/QGraphicsEllipseItem>

namespace phillib
{
  class Ball : public QGraphicsEllipseItem
  {
  public:
    Ball(const QPointF &pos, const QPointF &v, const float m = 1.0f, const float radius = 5.0f, const QColor& = Qt::white);
    virtual ~Ball() {}
    void iterate();
    const QPointF &v(void) const { return _v; }
    void setV(const QPointF &v) { _v = v; }
    void collide(Ball& ball);
    enum
    {
      Type = UserType + 1
    };
    virtual int type() const override { return Type; }
    void setDelete(){_flagDelete = true;}
    bool flagDelete(void)const{return _flagDelete;}
    const qreal m(void)const{return _m;}
    // virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // virtual QRectF boundingRect() const override;

  private:
    QPointF _v;
    bool _flagDelete = false;
    qreal _m = 1.0f;
  };
}
#endif
