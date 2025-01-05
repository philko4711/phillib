#include "SnakeGui.h"
#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>
#include <cmath>
namespace phillib
{
SnakeGui::SnakeGui():_guiUi(new Ui::MainWindow)
  {
    _guiUi->setupUi(this);
    _guiUi->widget->setScene(new QGraphicsScene(static_cast<QRectF>(this->rect())));
  }

bool SnakeGui::addPixel(const unsigned int col, const unsigned int row)
{
  std::shared_ptr<QGraphicsRectItem> item = std::make_shared<QGraphicsRectItem>(static_cast<qreal>(50 * col), static_cast<qreal>(50 * row), 50.0, 50.0);
  QPen pen(Qt::SolidLine);
  pen.setColor(Qt::green);
  QBrush brush(Qt::SolidPattern);
  brush.setColor(Qt::green);
  item->setPen(QPen(pen));
  item->setBrush(brush);
  _pixelsActive.push_back(item);
  _guiUi->widget->scene()->addItem(item.get());
  this->update();
  return true;
}

bool SnakeGui::rmPixel(const unsigned int col, const unsigned int row)
{
  qDebug() << __PRETTY_FUNCTION__ << "(line 29, SnakeGui.cpp)";
  auto list = _guiUi->widget->scene()->items();
  
  for(auto iter = list.begin(); iter < list.end(); iter++)
  {
    const unsigned int itemX = static_cast<unsigned int>(std::round((*iter)->boundingRect().x()));
    const unsigned int itemY = static_cast<unsigned int>(std::round((*iter)->boundingRect().y()));
    qDebug() << __PRETTY_FUNCTION__ << " itemX " << itemX << " itemY " << itemY << std::round((*iter)->boundingRect().x());
    if((itemX == col * 50) && (itemY == row * 50))
    {
      _guiUi->widget->scene()->removeItem(*iter);
      //_pixelsActive.erase(iter);
      qDebug() << __PRETTY_FUNCTION__ << "duuuu(line 37, SnakeGui.cpp)";
    }
  }
  this->update();
  return true;
}

void SnakeGui::rmAllPixels()
{
  auto list = _guiUi->widget->scene()->items();
  for(auto& iter : list)
    _guiUi->widget->scene()->removeItem(iter);
 _pixelsActive.clear();   
}

bool SnakeGui::pixel(const unsigned int col, const unsigned int row)
{
  for(auto& iter : _pixelsActive)
  {
    const unsigned int itemX = static_cast<unsigned int>(std::round(iter->boundingRect().x()));
    const unsigned int itemY = static_cast<unsigned int>(std::round(iter->boundingRect().y()));
    if((itemX == col * 50) && (itemY == row * 50))
      return true;
  }
  return false;
}

void SnakeGui::updateDisplay(const utils::Fifo<ContentSnake>& content, const ContentSnake& food)
{
  this->rmAllPixels();
  for(unsigned int i = 0; i < content.size(); i++)
  {
    //if(!this->pixel(content[i].col(), content[i].row()))
      this->addPixel(content[i].col(), content[i].row());
  }
  this->addPixel(food.col(), food.row());
  this->update();
}

void SnakeGui::keyPressEvent(QKeyEvent* event)
{
  //qDebug() << __PRETTY_FUNCTION__ << "(line 81, SnakeGui.cpp)";
  auto key = event->key();
  switch(key)
  {
    case Qt::Key_W:
    case Qt::Key_A:
    case Qt::Key_D:  
    case Qt::Key_S:
      emit this->key(key);
      break;
    default:
      break;   //all other keys are ignored  
  }
}

}
