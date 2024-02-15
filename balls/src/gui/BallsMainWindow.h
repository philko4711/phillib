#ifndef PHILLIB_BALLSMAINWINDOW_H_
#define PHILLIB_BALLSMAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include "ui_main_window_balls.h"
#include <memory>
namespace phillib
{
  class CollidingItems
  {
    public:
      CollidingItems(QGraphicsItem* item0, QGraphicsItem* item1):_item0(item0), _item1(item1){}
      virtual ~CollidingItems(){}
    private:
      QGraphicsItem* _item0;
      QGraphicsItem* _item1;
  };

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
    std::vector<CollidingItems> collidingItems(void)const;
    private:
    void init();
    std::unique_ptr<Ui::MainWindow> _guiUi;

};
}
#endif

