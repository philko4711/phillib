#include "FractalLab.h"
//#include <QtWidgets/QGraphicsEllipseItem>
#include <QtWidgets/QGraphicsLineItem>
namespace phillib
{

std::unique_ptr<FractalLab> FractalLab::_instance = nullptr;

FractalLab::FractalLab():_guiUi(new Ui::MainWindow)
  {
    _guiUi->setupUi(this);
    _guiUi->graphicsView->setScene(new QGraphicsScene);
    // QLineF line;
    // line.setP1(this->rect().center());
    // line.setP2(this->rect().center() + QPointF(0.0f, 20.0f));
    
    // QGraphicsLineItem* item = new QGraphicsLineItem(line);
    // QPen pen(Qt::SolidLine);
    // pen.setColor(Qt::green);
    // pen.setWidth(5.0f);
    // QBrush brush(Qt::SolidPattern);
    // brush.setColor(Qt::green);
    // item->setPen(pen);
    // //item->setBrush(brush);
    // item->setPos(this->rect().center());
    // //item->setRotation(10.0f);
    // _guiUi->graphicsView->scene()->addItem(item);
  }

FractalLab& FractalLab::instance()
{
  if(!_instance)
    _instance = std::unique_ptr<FractalLab>(new FractalLab);
  return *_instance;  
}

void FractalLab::addItem(std::shared_ptr<QGraphicsItem>& item)
{
  _guiUi->graphicsView->scene()->addItem(item.get());
  _items.push_back(item);
  this->update();
}

}
