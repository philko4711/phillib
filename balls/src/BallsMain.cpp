#include "BallsMain.h"
#include <QtCore/QDebug>
namespace phillib
{
BallsMain::BallsMain(const int nBalls):_gui(800, 600)
  {
    _timerMain.start(10);
    connect(&_timerMain, SIGNAL(timeout()), this, SLOT(iterate()));
    _gui.show();
  }

void BallsMain::iterate()
{
  const QRectF sceneRect = _gui.sceneRect();
  
  for(auto& iter : _balls)
  {
    iter->iterate();
    if(!sceneRect.contains(iter->itemGraphic().pos()))
    {
      
      QPointF pos = iter->itemGraphic().pos();
      QPointF v = iter->v();
      //qDebug() << __PRETTY_FUNCTION__ << " Balls left the area: " << pos;
      if((pos.x() > sceneRect.right()) || (pos.x() < sceneRect.left())) 
      {
        pos.setX(pos.x() - iter->v().x());
        v.setX(v.x() * -1.0f); 
      }
      // else if(pos.x() < sceneRect.left())
      // {
      //   pos.setX(pos.x() - iter->v().x());
      //   v.setX(v.x() * -1.0f); 
      // }
      else if((pos.y() > sceneRect.bottom()) || (pos.y() < sceneRect.top()))
      {
        pos.setY(pos.y() - iter->v().y());
        v.setY(v.y() * -1.0f); 
      }
      iter->setPos(pos);
      iter->setV(v);
    }
  }
  auto collisions = _gui.collidingItems();
  if(collisions.size())
    qDebug() << __PRETTY_FUNCTION__ << " Items collide";
  _gui.update();
}

void BallsMain::addBall()
{

}

void BallsMain::addBall(const QPointF& pos, const QPointF& v)
{
  auto ptr = std::make_shared<Ball>(pos, v);
  _gui.addBallItem(ptr->itemGraphic());
  _balls.push_back(ptr);
  _gui.update();
}

}
