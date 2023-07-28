#ifndef PHILLIB_GAME_OF_LIFE_PREY_H_
#define PHILLIB_GAME_OF_LIFE_PREY_H_


#include "ObjectMap.h"
#include "IAgent.h"
#include <memory>
#include <QtCore/QDebug>
#include <QtGui/QPainter>

namespace phillib
{
namespace game_of_life
{
  class GraphicItemPrey : public QGraphicsItem
{
public:
  enum
  {
    Type = UserType + 1
  };
  GraphicItemPrey(QGraphicsItem* parent = nullptr) {}
  virtual ~GraphicItemPrey() {}
  virtual QRectF boundingRect() const override { return QRectF(0, 0, 10, 10); }   //todo: baseclass
  virtual void   paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override //Todo: baseclass
  {
    painter->save();
    QPen   pen(Qt::SolidLine);
    QBrush brush(Qt::SolidPattern);
    // QColor color(Qt::green);
    // float amount = static_cast<float>(_amount);

    // color.setAlphaF((amount / _amountInitial));
    pen.setColor(_color);
    brush.setColor(_color);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(this->boundingRect());
    painter->restore();
  }

  virtual int type(void) const override { return Type; }
  void        setColor(const QColor& color) { _color = color; }

private:
  QColor _color;
};

  class Prey : public ObjectMap, IAgent, std::enable_shared_from_this<Prey>
  {
    public:
    Prey(const QPoint& pos);
    virtual ~Prey(){}
    std::shared_ptr<Prey> ptr(){return shared_from_this();}
    virtual uint8_t health(void)const{return 100;}
    virtual void iterate(){}
    virtual Type type(void)const{return IObjectMap::Type::PREY;}
    void move(){ObjectMap::_pos = QPoint(0, 0);}
    private:
      float _health;
};
}
}
#endif

