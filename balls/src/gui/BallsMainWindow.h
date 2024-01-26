#ifndef PHILLIB_BALLSMAINWINDOW_H_
#define PHILLIB_BALLSMAINWINDOW_H_

#include <QtWidgets/QMainWindow>

namespace phillib
{
  class BallsMainWindow : public QMainWindow
  {
    //Q_OBJECT
    public:
    BallsMainWindow();
    BallsMainWindow(const int w, const int h);
    virtual ~BallsMainWindow(){}
    void addBall();
    private:
    void init();
};
}
#endif

