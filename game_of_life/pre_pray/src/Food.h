#ifndef PHILLIB_GAME_OF_LIFE_FOOD_H_
#define PHILLIB_GAME_OF_LIFE_FOOD_H_


#include "ObjectMap.h"
#include <QtCore/QDebug>
#include <QtWidgets/QGraphicsItem>
#include <memory>

namespace phillib
{
namespace game_of_life
{
  class Food : public QGraphicsItem, std::enable_shared_from_this<Food>
  {
    public:
    enum {Type = UserType + 1};
    Food(const QPointF& pos);
    virtual ~Food(){qDebug() << __PRETTY_FUNCTION__;}
    std::shared_ptr<Food> ptr(){return shared_from_this();}
    virtual uint8_t health(void)const;//{return 100;}
    virtual int type(void)const override{return Type;}
    unsigned int wither(const unsigned int nFreeNeighbours = 8);
    virtual QRectF boundingRect()const override{return QRectF(0, 0, 10, 10);}
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr)override;
    private:
      void spread();
      unsigned int _amount;
      const float _amountInitial;
};
}
}
#endif

