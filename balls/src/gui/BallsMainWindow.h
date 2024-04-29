#ifndef PHILLIB_BALLSMAINWINDOW_H_
#define PHILLIB_BALLSMAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include "ui_main_window_balls.h"
#include "Ball.h"
#include <memory>
namespace phillib
{
  class CollidingItems
  {
    public:
      CollidingItems(QGraphicsItem* item0, QGraphicsItem* item1):_item0(item0), _item1(item1){}
      virtual ~CollidingItems(){}
      QGraphicsItem* item0(){return _item0;}
      QGraphicsItem* item1(){return _item1;}
      bool operator==(const CollidingItems& var)
      {
        if((var._item0 == _item0)&&(var._item1 == _item1))
            return true;
        else if((var._item1 == _item0)&&(var._item0 == _item1))
            return true;
        return false;    
      }
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
      void addBallItem(Ball& item);
      const QRectF sceneRect(void)const{return _guiUi->graphicsView->sceneRect();}
      std::vector<CollidingItems> collidingItems(void)const;
      void removeItem(QGraphicsItem* item);
    signals:
      void pause(const bool state);
      void slow(const bool state);
      void iterate(const bool direction);
    public slots:
      void buttonPauseChanged(const bool state);
      void buttonSlowChanged(const bool state);
      void buttonIterateForwardClicked();
      void buttonIterateBackwardClicked();    
    private:
      void init();
      void resetCheckedButtonSlow();
      void resetCheckedButtonPause();
      std::unique_ptr<Ui::MainWindow> _guiUi;

};
}
#endif

