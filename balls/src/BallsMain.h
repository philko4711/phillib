#ifndef PHILLIB_BALLSMAIN_H_
#define PHILLIB_BALLSMAIN_H_


#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <vector>

#include "Ball.h"
#include "gui/BallsMainWindow.h"

namespace phillib
{
  class BallsMain : public QObject
  {
    Q_OBJECT
    public:
    BallsMain(const int nBalls);
    virtual ~BallsMain(){}
    void addBall();
    void addBall(const QPointF& pos, const QPointF& v, const float m = 1.0f, const float radius = 5.0f, const QColor& = Qt::white);
    void removeBall(std::vector<std::shared_ptr<Ball> >::iterator ball);
    public slots:
      void iterate(const bool forward = true);
      void pause(const bool state);
      void slow(const bool state);
    private:  
      BallsMainWindow _gui;
      std::vector<std::shared_ptr<Ball> > _balls;
      QTimer _timerMain;
};
}
#endif

