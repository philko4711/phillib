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
    qDebug() << __PRETTY_FUNCTION__ << " Adding scene with rect " << rectF;
    _guiUi->graphicsView->setScene(new QGraphicsScene(rectF));
    this->setStyleSheet("background-color:black;");
  }

  // void BallsMainWindow::addBall()
  // {
  //   std::vector<float> rdsX;
  //   std::vector<float> rdsY;
  //   const QRectF &rect = _guiUi->graphicsView->scene()->sceneRect();
  //   utils::randomReal(1, rdsY, rect.bottomLeft().ry(), rect.topRight().ry());
  //   utils::randomReal(1, rdsX, rect.bottomLeft().rx(), rect.topRight().rx());

  //   //std::shared_ptr<QGraphicsEllipseItem> item = std::make_shared<QGraphicsEllipseItem>();
  //   static std::shared_ptr<QGraphicsEllipseItem> item = std::shared_ptr<QGraphicsEllipseItem>(new QGraphicsEllipseItem);

  //   item->setRect(0.0f, 0.0f, 50.0f, 50.0f);
  //   QBrush brush(Qt::SolidPattern);
  //   QPen pen(Qt::SolidLine);
  //   pen.setWidth(1);
  //   pen.setColor(Qt::green);
  //   brush.setColor(Qt::green);
  //   item->setBrush(brush);
  //   item->setPen(pen);
  //   //item->setVisible(true);
  //   item->setPos(*rdsX.begin(), *rdsY.begin());
  //   //item->setPos(QPointF(0.0f, 0.0f));
  //   qDebug() << __PRETTY_FUNCTION__ << "Adding object with rect " << item->rect() << " and pos " << item->pos();
  //   _guiUi->graphicsView->scene()->addItem(item.get());
  //   _guiUi->graphicsView->update();
  // }

  void BallsMainWindow::addBallItem(Ball &item)
  {
    // item.setRect(0.0f, 0.0f, 5.0f, 5.0f);
    // QBrush brush(Qt::SolidPattern);
    // QPen pen(Qt::SolidLine);
    // pen.setWidth(1);
    // pen.setColor(Qt::green);
    // brush.setColor(Qt::green);
    // item.setBrush(brush);
    // item.setPen(pen);
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
          collisions.push_back(CollidingItems(iter0, iter1));
        }
      }
    }
    return collisions;
  }

  void BallsMainWindow::removeItem(QGraphicsItem *item)
  {
    _guiUi->graphicsView->scene()->removeItem(item);
  }
}
