#include "GrView.h"
#include "GraphScExample.h"
#include <QtCore/QDebug>
#include <QtMultimedia/QCameraInfo>
#include <QtMultimediaWidgets/QCameraViewfinder>

#include <phillib_utils/random.h>
namespace phillib {
namespace qt {
GrView::GrView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(parent) ,_camera("/dev/video0"){
  this->setScene(scene);
  this->setMouseTracking(true);
   QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
  for(auto& iter : cameras) {
      
      qDebug() << __PRETTY_FUNCTION__ << " " << iter;
  } 
  //QCameraViewfinder* view = new QCameraViewfinder;
  MyVideoSurface* view = new MyVideoSurface;
  _camera.setViewfinder(view);
  //view->show();
  _camera.start();
  connect(view, SIGNAL(newFrame(QImage)), this, SLOT(newCameraFrame(QImage)));
}

void GrView::mousePressEvent(QMouseEvent *event) {
  // qDebug() << __PRETTY_FUNCTION__ << "entry";
  auto scene = this->scene();
  auto point = this->mapToScene(event->pos());
  if ((event->button() == Qt::LeftButton)) {
    dynamic_cast<GraphScExample *>(scene)->drawPoint(point);
    //scene->addEllipse(point.x(), point.y(), 2.0, 2.0, QPen(QBrush(Qt::green), 50), QBrush(Qt::green, Qt::SolidPattern));
    scene->addItem(new ColoredEllipse(point.x(), point.y(), 20.0, 10.0, Qt::green));//, QPen(QBrush(Qt::green), 50), QBrush(Qt::green, Qt::SolidPattern));
  }
  auto items = scene->items();
  if(items.size())
  {
    qDebug() << __PRETTY_FUNCTION__ << "1";
  std::vector<int> rd;
  std::vector<int> r;
  std::vector<int> g;
  std::vector<int> b;



  phillib::utils::randomInts(1, rd, 0, items.size() - 1);
  phillib::utils::randomInts(1, r, 0, 255);
  phillib::utils::randomInts(1, g, 0, 255);
  phillib::utils::randomInts(1, b, 0, 255);
  qDebug() << __PRETTY_FUNCTION__ << "2 " << *rd.begin();

  dynamic_cast<ColoredEllipse*>(items[*rd.begin()])->setColor(QColor(*r.begin(), *g.begin(), *b.begin()));
  }
  // for(auto& iter : scene->items())
  // {
  //   //qDebug() << __PRETTY_FUNCTION__ << " " << iter->type() == QGraphicsEllipseItem;
  //   auto ptr = qgraphicsitem_cast<QGraphicsEllipseItem*>(iter);
  //   if(ptr)
  //     qDebug() << __PRETTY_FUNCTION__ << " hehe";
  // } 
  // else if ((event->button() == Qt::MiddleButton))
  //   this->centerOn(this->mapToScene(event->pos()));
  this->update();
}

void GrView::mouseMoveEvent(QMouseEvent *event) {

  if (event->buttons() & Qt::MiddleButton) {
    event->accept();
    //qDebug() << __PRETTY_FUNCTION__ << " middle button active";
    this->centerOn(this->mapToScene(event->pos()));
    this->update();
  } else
    QGraphicsView::mouseMoveEvent(event);
}

void GrView::wheelEvent(QWheelEvent *event) {
  event->accept();
  // qDebug() << __PRETTY_FUNCTION__ << "";
  //_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  if (event->delta() > 0)
    this->centerOn(this->mapToScene(event->pos()));
  else
    this->centerOn(this->mapToScene(this->rect().center()));

  qreal delta = 1 + (event->delta() > 0 ? 0.1 : -0.1);
  this->scale(delta, delta);
}

void GrView::newCameraFrame(QImage image)
{
  dynamic_cast<GraphScExample *>(this->scene())->setImage(image);
this->update();
}
} // namespace qt
} // namespace phillib
