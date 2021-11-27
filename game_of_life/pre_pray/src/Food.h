#ifndef PHILLIB_GAME_OF_LIFE_FOOD_H_
#define PHILLIB_GAME_OF_LIFE_FOOD_H_

#include "IObjectMap.h"
#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsItem>
#include <memory>

namespace phillib
{
namespace game_of_life
{
class GraphicItemFood : public QGraphicsItem
{
public:
  enum
  {
    Type = UserType + 1
  };
  GraphicItemFood(QGraphicsItem* parent = nullptr) {}
  virtual ~GraphicItemFood() {}
  virtual QRectF boundingRect() const override { return QRectF(0, 0, 10, 10); }
  virtual void   paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override
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
class Food : public IObjectMap, std::enable_shared_from_this<Food>
{
public:
  // enum {Type = UserType + 1};
  Food(); // const QPointF& pos
  virtual ~Food() { qDebug() << __PRETTY_FUNCTION__; }
  std::shared_ptr<Food> ptr() { return shared_from_this(); }
  virtual uint8_t       health(void) const; //{return 100;}
  // virtual int type(void)const override{return Type;}
  unsigned int wither(const unsigned int nFreeNeighbours = 8);
  // virtual QRectF boundingRect()const override{return QRectF(0, 0, 10, 10);}
  // virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr)override;
  virtual IObjectMap::Type       typeObjectMap(void) const override { return IObjectMap::Type::FOOD; }
  virtual const QPoint&          idx(void) const override { return _cellIdx; }
  virtual void                   setIdx(const QPoint& idx) override; //{_cellIdx = idx;}
  std::shared_ptr<QGraphicsItem> item(void) { return _graphic; }

private:
  void                             spread();
  unsigned int                     _amount;
  const float                      _amountInitial;
  QPoint                           _cellIdx;
  std::shared_ptr<GraphicItemFood> _graphic;
};
} // namespace game_of_life
} // namespace phillib
#endif
