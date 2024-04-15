#include "Ball.h"
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <cmath>

namespace phillib
{
  Ball::Ball(const QPointF &pos, const QPointF &v, const float m) : _v(v), _m(m)
  {
    qDebug() << __PRETTY_FUNCTION__ << "entry";

    // this->setVisible(true);
    this->setPos(pos);
    this->setFlag(ItemIsMovable);
    this->setRect(0.0f, 0.0f, 5.0f, 5.0f);   //TODO: make adjustable
    QBrush brush(Qt::SolidPattern);
    QPen pen(Qt::SolidLine);
  
     pen.setWidth(1);
     pen.setColor(Qt::green);
     brush.setColor(Qt::green);
     this->setBrush(brush);
     this->setPen(pen);

    qDebug() << __PRETTY_FUNCTION__ << "exit";
  }

  void Ball::iterate()
  {
    QPointF pos = this->pos();
    pos += _v;
    this->setPos(pos);
  }

  void Ball::collide(Ball& ball)
  {
    const float phi = std::atan2(ball.pos().y() - this->pos().y() , ball.pos().x() - this->pos().x());
    qDebug() << __PRETTY_FUNCTION__ << " phi " << phi;
    const QPointF v1 = this->v();
    const QPointF v2 = ball.v();
    const float const1 = ((this->m() - ball.m()) * (v1.x() * std::cos(phi) + v1.y() * std::sin(phi)) + 2.0f * ball.m() * (v2.x() * std::cos(phi) + v2.y() * std::sin(phi))) / (this->m() + ball.m());
    const float u1x = (v1.x() * std::sin(phi) - v1.y() * std::cos(phi)) * std::sin(phi) +  const1 * std::cos(phi);
    const float u1y = (-v1.x() * std::sin(phi) + v1.y() *std::cos(phi)) * std::cos(phi) +  const1 * std::sin(phi);

    const float const2 = ((ball.m()- this->m()) * (v2.x() * std::cos(phi) + v2.y() * std::sin(phi)) + 2.0f * this->m() * (v1.x() * std::cos(phi) + v1.y() * std::sin(phi))) / (this->m() + ball.m());
    const float u2x = (v2.x() * std::sin(phi) - v2.y() * std::cos(phi)) * std::sin(phi) +  const2 * std::cos(phi);
    const float u2y = (-v2.x() * std::sin(phi) + v2.y() * std::cos(phi)) * std::cos(phi) +  const2 * std::sin(phi);

    const QPointF v_s0(u1x, u1y);
    this->setV(v_s0);
    const QPointF v_s1(u2x, u2y);
    ball.setV(v_s1);
    qDebug() << __PRETTY_FUNCTION__ << "vnew: " << v_s0 << " " << v_s1;
    for(unsigned int i = 0; i < 5; i++)
    {
      ball.iterate();
      this->iterate();
    }
  }

  // QRectF Ball::boundingRect() const
  // {
  //   //     this->setRect(0.0f, 0.0f, 5.0f, 5.0f);   //TODO: make adjustable
  //   return QRectF(0.0f, 0.0f, 5.0f, 5.0f);
  // }

  // void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
  // {
  //   QBrush brush(Qt::SolidPattern);
  //   QPen pen(Qt::SolidLine);
  //   painter->save();
  //   pen.setWidth(1);
  //   pen.setColor(Qt::green);
  //   brush.setColor(Qt::green);
  //   painter->setBrush(brush);
  //   painter->setPen(pen);
  //   painter->drawEllipse(this->boundingRect());
  //   painter->restore();
  // }

}
