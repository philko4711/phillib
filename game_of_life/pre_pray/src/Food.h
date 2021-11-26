#ifndef PHILLIB_GAME_OF_LIFE_FOOD_H_
#define PHILLIB_GAME_OF_LIFE_FOOD_H_


#include "IObjectMap.h"
#include <QtCore/QDebug>
#include <QtWidgets/QGraphicsItem>
#include <memory>

namespace phillib
{
namespace game_of_life
{
  class Depp : public IObjectMap
  {
    public:
    Depp(){}
    virtual ~Depp(){}
    virtual const QPoint& idx(void)const override{return QPoint(0,0);}
    virtual void setIdx(const QPoint& idx)override{;}
    virtual IObjectMap::Type typeObjectMap(void)const override{return IObjectMap::Type::FOOD;}
  };
  class Food : public IObjectMap, QGraphicsItem, std::enable_shared_from_this<Food>
  {
    public:
    enum {Type = UserType + 1};
    Food();   //const QPointF& pos
    virtual ~Food(){qDebug() << __PRETTY_FUNCTION__;}
    std::shared_ptr<Food> ptr(){return shared_from_this();}
    virtual uint8_t health(void)const;//{return 100;}
    virtual int type(void)const override{return Type;}
    unsigned int wither(const unsigned int nFreeNeighbours = 8);
    virtual QRectF boundingRect()const override{return QRectF(0, 0, 10, 10);}
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = nullptr)override;
    virtual IObjectMap::Type typeObjectMap(void)const override{return IObjectMap::Type::FOOD;}
    virtual const QPoint& idx(void)const override{return _cellIdx;}
    virtual void setIdx(const QPoint& idx)override;//{_cellIdx = idx;}
    private:
      void spread();
      unsigned int _amount;
      const float _amountInitial;
      QPoint _cellIdx;
};
}
}
#endif

