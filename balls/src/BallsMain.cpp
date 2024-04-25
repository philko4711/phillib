#include "BallsMain.h"
#include <QtCore/QDebug>
#include <random>
namespace phillib
{
  BallsMain::BallsMain(const int nBalls) : _gui(800, 600)
  {
    _timerMain.start(10);
    connect(&_timerMain, SIGNAL(timeout()), this, SLOT(iterate()));
    _gui.show();
     for(auto i = 0; i < nBalls; i++)
       this->addBall();
    qDebug() << __PRETTY_FUNCTION__ << "Exit";  
  }

  void BallsMain::iterate()
  {
    const QRectF sceneRect = _gui.sceneRect();

    for (auto iter = _balls.begin(); iter < _balls.end(); iter++)
    {
      if((*iter)->flagDelete())
      {
        this->removeBall(iter);
      }
      (*iter)->iterate();
      if (!sceneRect.contains((*iter)->pos()))
      {

        QPointF pos = (*iter)->pos();
        QPointF v = (*iter)->v();
        // qDebug() << __PRETTY_FUNCTION__ << " Balls left the area: " << pos;
        if ((pos.x() > sceneRect.right()) || (pos.x() < sceneRect.left()))
        {
          pos.setX(pos.x() - (*iter)->v().x());
          v.setX(v.x() * -1.0f);
        }
        // else if(pos.x() < sceneRect.left())
        // {
        //   pos.setX(pos.x() - iter->v().x());
        //   v.setX(v.x() * -1.0f);
        // }
        else if ((pos.y() > sceneRect.bottom()) || (pos.y() < sceneRect.top()))
        {
          pos.setY(pos.y() - (*iter)->v().y());
          v.setY(v.y() * -1.0f);
        }
        (*iter)->setPos(pos);
        (*iter)->setV(v);
      }
    }
    auto collisions = _gui.collidingItems();
    if (collisions.size())
    {
      std::vector<QGraphicsItem*> toDelete;
     // unsigned int ctr = 0;
      for(auto& iter : collisions)
      {
      //  qDebug() << __PRETTY_FUNCTION__ << " collision nbr " << ctr++;
        dynamic_cast<Ball*>(iter.item0())->collide(*dynamic_cast<Ball*>(iter.item1()));
      //  dynamic_cast<Ball*>(iter.item0())->setDelete();
      //  dynamic_cast<Ball*>(iter.item1())->setDelete();
      }
    //abort();  
    }
    _gui.update();
    
  }

  void BallsMain::addBall()
  {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> vs(1.0, 10.0);
    std::uniform_real_distribution<float> xs(0.0, 600.0);
    std::uniform_real_distribution<float> ys(0.0, 600.0);
    QPointF v(vs(mt), vs(mt));
    QPointF pos(xs(mt), ys(mt));
    qDebug() << __PRETTY_FUNCTION__ << "adding ball with pos " << pos << " and v " << v;
    this->addBall(pos, v);
  }

  void BallsMain::addBall(const QPointF &pos, const QPointF &v, const float m, const float radius, const QColor& color)
  {
    auto ptr = std::make_shared<Ball>(pos, v, m, radius, color);
    _gui.addBallItem(*ptr.get());
    _balls.push_back(ptr);
    _gui.update();
  }

  void BallsMain::removeBall(std::vector<std::shared_ptr<Ball> >::iterator ball)
  {
    _gui.removeItem(ball->get());
    _balls.erase(ball);      
  }

}
