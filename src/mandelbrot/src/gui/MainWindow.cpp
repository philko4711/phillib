#include "MainWindow.h"
#include <QtCore/QDebug>
#include <iostream>
namespace phillib
{
namespace qt
{
MainWindow::MainWindow()
    : _guiUi(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow))
{
  _guiUi->setupUi(this);
  this->resize(800, 800);
  this->show();
  this->setMouseTracking(true);
}

void MainWindow::wheelEvent(QWheelEvent* event)
{
  event->accept();
  // qDebug() << __PRETTY_FUNCTION__ << " " << event->angleDelta();
  QPoint centerDelta = event->pos() - this->rect().center();
  // qDebug() << __PRETTY_FUNCTION__ << " " << centerDelta;
  emit this->magnify(centerDelta, event->angleDelta());
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
  event->accept();
  _magnifier = new QRect(event->pos(), QSize(0, 0));
  QVector<QRect> rects;
  rects.push_back(*_magnifier);
  _guiUi->widget->setRects(rects);
  this->update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
  event->accept();
  
  QVector<QRect> rects;
  _guiUi->widget->setRects(rects);
  if(_magnifier->width() * _magnifier->height() > 10)
    emit this->magnify(*_magnifier);
  delete _magnifier;
  this->update();
}
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
  event->accept();
  if(_magnifier)
  {
    _magnifier->setBottomRight(event->pos());
    _magnifier->setWidth(_magnifier->height()); //toDo: for future add correct ratio
      
    QVector<QRect> rects;
    rects.push_back(*_magnifier);
    _guiUi->widget->setRects(rects);
  }
  this->update();
}

} // namespace qt
} // namespace phillib
