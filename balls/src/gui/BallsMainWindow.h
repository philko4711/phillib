#ifndef PHILLIB_BALLSMAINWINDOW_H_
#define PHILLIB_BALLSMAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include "ui_main_window_balls.h"
#include <memory>
namespace phillib
{
  class BallsMainWindow : public QMainWindow
  {
    Q_OBJECT
    public:
    BallsMainWindow();
    BallsMainWindow(const int w, const int h);
    virtual ~BallsMainWindow(){}
    void addBall();
    void addBallItem(QGraphicsEllipseItem& item);
    const QRectF sceneRect(void)const{return _guiUi->graphicsView->sceneRect();}
    private:
    void init();
    std::unique_ptr<Ui::MainWindow> _guiUi;

};
}
#endif

