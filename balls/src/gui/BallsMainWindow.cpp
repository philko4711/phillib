#include "BallsMainWindow.h"
#include "phillib_utils/random.h"
#include <vector>
namespace phillib
{
BallsMainWindow::BallsMainWindow()
  {
    this->setWindowState(Qt::WindowFullScreen);
    this->init();
  }

  BallsMainWindow::BallsMainWindow(const int w, const int h)
  {
    this->setGeometry(0, 0, w, h);
    this->init();
  }

  void BallsMainWindow::init()
  {
    this->setStyleSheet("background-color:black;");
  }

void BallsMainWindow::addBall()
{
  std::vector<float> rds;
  //utils::randomReal(2, rds, );

}

}
