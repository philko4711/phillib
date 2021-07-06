#include "MainWindow.h"
#include <iostream>
#include <QtCore/QDebug>
namespace phillib
{
namespace qt
{
MainWindow::MainWindow():_guiUi(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow))
  {
    _guiUi->setupUi(this);
    this->resize(800, 800);
    this->show();
  }

void MainWindow::wheelEvent(QWheelEvent* event)
{
  event->accept();
  //qDebug() << __PRETTY_FUNCTION__ << " " << event->angleDelta();
  QPoint centerDelta = event->pos() - this->rect().center();
  //qDebug() << __PRETTY_FUNCTION__ << " " << centerDelta;
  emit this->magnify(centerDelta, event->angleDelta());
}

}
}
