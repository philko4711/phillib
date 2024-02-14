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
    void addBall(const QPointF& pos, const QPointF& v);
    public slots:
      void iterate();
    private:  
      BallsMainWindow _gui;
      std::vector<std::shared_ptr<Ball> > _balls;
      QTimer _timerMain;
};
}
#endif

