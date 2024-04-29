#include "BallsMainWindow.h"
#include <phillib_utils/random.h>
#include <vector>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtCore/QDebug>
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
    _guiUi = std::make_unique<Ui::MainWindow>();
    _guiUi->setupUi(this);
    QRectF rectF(this->rect());
    //qDebug() << __PRETTY_FUNCTION__ << " Adding scene with rect " << rectF;
    _guiUi->graphicsView->setScene(new QGraphicsScene(rectF));
    connect(_guiUi->pushButtonPause, SIGNAL(toggled(bool)), this, SLOT(buttonPauseChanged(const bool)));
    connect(_guiUi->pushButtonSlow, SIGNAL(toggled(bool)), this, SLOT(buttonSlowChanged(const bool)));
    connect(_guiUi->pushButtonIterateForward, SIGNAL(clicked(bool)), this, SLOT(buttonIterateForwardClicked()));
    connect(_guiUi->pushButtonIterateBackward, SIGNAL(clicked(bool)), this, SLOT(buttonIterateBackwardClicked()));
  }

  void BallsMainWindow::addBallItem(Ball &item)
  {
    _guiUi->graphicsView->scene()->addItem(&item);
  }

  std::vector<CollidingItems> BallsMainWindow::collidingItems(void) const
  {
    auto items = _guiUi->graphicsView->scene()->items();
    std::vector<CollidingItems> collisions;
    for (auto &iter0 : items)
    {
      for (auto &iter1 : items)
      {
        if (iter0 == iter1)
          continue;
        if (iter0->collidesWithItem(iter1))
        {
          CollidingItems var(iter0, iter1);
          bool found = false;
          for(auto& iter3 : collisions)
            if(iter3 == var)
            {
              found = true;
              break;
            }
          if(!found)  
          collisions.push_back(var);
        }
      }
    }
    return collisions;
  }

  void BallsMainWindow::removeItem(QGraphicsItem *item)
  {
    _guiUi->graphicsView->scene()->removeItem(item);
  }

  void BallsMainWindow::buttonPauseChanged(const bool state)
  {
    if(state == true)
      this->resetCheckedButtonSlow();
    emit this->pause(state);    
  }

  void BallsMainWindow::buttonSlowChanged(const bool state)
  {
    if(state == true)
      this->resetCheckedButtonPause();
    emit this->slow(state);    
  }

  void BallsMainWindow::buttonIterateForwardClicked()
  {
    this->resetCheckedButtonPause();
    this->resetCheckedButtonSlow();
    emit this->iterate(true);
  }

  void BallsMainWindow::buttonIterateBackwardClicked()
  {
    this->resetCheckedButtonPause();
    this->resetCheckedButtonSlow();
    emit this->iterate(false);
  }

  void BallsMainWindow::resetCheckedButtonSlow()
  {
    if(_guiUi->pushButtonSlow->isChecked())
        _guiUi->pushButtonSlow->setChecked(false);        
  }

  void BallsMainWindow::resetCheckedButtonPause()
  {
    if(_guiUi->pushButtonPause->isChecked())
        _guiUi->pushButtonPause->setChecked(false);
  }
}
