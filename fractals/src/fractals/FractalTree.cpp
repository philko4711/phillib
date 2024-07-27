#include "FractalTree.h"
#include "FractalLab.h"
#include <QtWidgets/QGraphicsLineItem>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtGui/QPen>
#include <QtCore/QDebug>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <Eigen/Dense>
#include <cmath>

#define ANGLE M_PI / 8.0f

namespace phillib
{
  FractalTree::FractalTree(const QLineF &lineInitial)
  {
    _lines.push_back(lineInitial);
    std::shared_ptr<QGraphicsItem> ptr = std::shared_ptr<QGraphicsItem>(new QGraphicsLineItem(lineInitial));
    auto item = static_cast<QGraphicsLineItem*>(ptr.get());
    item->setPen(QPen(Qt::black, 0.5f));
      FractalLab::instance().addItem(ptr);
    FractalLab::instance().addItem(ptr);
    //add to gui
  }
  void FractalTree::iterate()
  {
    // QRandomGenerator rand;
    // QColor color(rand.bounded(0, 255), rand.bounded(0, 255), rand.bounded(0, 255) );
    std::vector<QLineF> linesNew;
    for(auto& iter : _lines)
    {
      qDebug() << __PRETTY_FUNCTION__ << "Line in: " << iter << " angle: " << iter.angle();
     
     Eigen::Vector2f p0(iter.p1().x(), iter.p1().y());
     Eigen::Vector2f p1(iter.p2().x(), iter.p2().y());
     Eigen::Vector2f m(p0 + 0.5f * (p1 - p0));

    Eigen::Vector2f v(p1 - p0);
    Eigen::Vector2f yAxis(10.0f, 0.0f);
    const float angle = std::acos(v.dot(yAxis) / (v.norm() * yAxis.norm()));      
    qDebug() << __PRETTY_FUNCTION__ << "angle : " << qRadiansToDegrees(angle);  

    Eigen::Vector2f dir(std::cos(angle + M_PI/8.0f), std::sin(angle + M_PI/8.0f));
    Eigen::Vector2f dir2(std::cos(angle - M_PI/8.0f), std::sin(angle - M_PI/8.0f));
    dir = dir / dir.norm();
    dir2 = dir2 / dir2.norm();
    //Eigen::Vector2f dir2(-std::cos(qDegreesToRadians(iter.angle() / 2.0f)), std::sin(qDegreesToRadians(iter.angle() / 2.0f)));
    QPointF pDir(dir.x(), dir.y());
    //qDebug() << __PRETTY_FUNCTION__ << "dir " << pDir << " new angle " << angle + 45.0f;
    Eigen::Vector2f p2 = m + dir * (v.norm() / 2.0f);
    Eigen::Vector2f p3 = m + dir2 * (v.norm() / 2.0f);
    //Eigen::Vector2f p3 = m + dir2 * v.norm() / 2.0f;
    //qDebug() << __PRETTY_FUNCTION__ << " p2 " << QPointF(p2.x(), p2.y());
     
     //std::shared_ptr<QGraphicsItem>  ptr = std::shared_ptr<QGraphicsEllipseItem>(new QGraphicsEllipseItem(m.x(), m.y(), 10, 10));
     //std::dynamic_pointer_cast<QGraphicsEllipseItem>(ptr)->setPen(QPen(1.0f));
    // std::dynamic_pointer_cast<QGraphicsEllipseItem>(ptr)->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    //  FractalLab::instance().addItem(ptr);
    QLineF lineNew(QLineF(QPointF(m.x(), m.y()), QPointF(p2.x(), p2.y())));  
    qDebug() << __PRETTY_FUNCTION__ << " adding line with angle " << lineNew.angle();
    linesNew.push_back(lineNew);
    lineNew = QLineF(QPointF(m.x(), m.y()), QPointF(p3.x(), p3.y()));  
    linesNew.push_back(lineNew);

    // lineNew = QLineF(iter.p1(),  QPointF(m.x(), m.y()));  
    // linesNew.push_back(lineNew);
    lineNew = QLineF(QPointF(m.x(), m.y()), iter.p2());  
    linesNew.push_back(lineNew);

    }
    QRandomGenerator rand;
    QColor color(rand.bounded(0, 255), rand.bounded(0, 255), rand.bounded(0, 255) );


    for(auto& iter : linesNew)
    {
      std::shared_ptr<QGraphicsItem> ptr(new QGraphicsLineItem(iter));
      auto item = static_cast<QGraphicsLineItem*>(ptr.get());
      item->setPen(QPen(color, 0.5f));
      FractalLab::instance().addItem(ptr);
      _lines.push_back(iter);
    }
  }
}
