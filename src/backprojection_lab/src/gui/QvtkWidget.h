/*
 * QvtkWidget.h
 *
 *  Created on: Aug 9, 2013
 *      Author: phil
 */

#ifndef QVTKWIDGET_H_
#define QVTKWIDGET_H_

#include <QVTKWidget.h>
#include <QColor>
#include <vector>

#include <vtkSmartPointer.h>
#include <vtkActor.h>

#include <vector>
#include <string>

#include <Eigen/Dense>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include "typedefs.h"

typedef std::vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d> > stdVecEig3d;

class vtkRenderer;
class vtkPolyData;
class vtkPoints;
class vtkUnsignedCharArray;
class vtkDoubleArray;
class vtkCellArray;


namespace deep_ohm
{
struct Line
{
  Line():
    _color(Qt::black),
    _width(1.0)
  {}
  Line(const Eigen::Vector3d& start, const Eigen::Vector3d& end):
    _start(start),
    _end(end),
    _color(Qt::white),
    _width(1.0)
    {}
  Line(const pcl::PointXYZ& start, const pcl::PointXYZ& end):
    _start(Eigen::Vector3d(static_cast<double>(start.x), static_cast<double>(start.y), static_cast<double>(start.z))),
    _end(Eigen::Vector3d(static_cast<double>(end.x), static_cast<double>(end.y), static_cast<double>(end.z))),
    _color(Qt::white),
    _width(1.0)
    {}
  Eigen::Vector3d _start;
  Eigen::Vector3d _end;
  QColor _color;
  float _width;
};
class QvtkWidget : public QVTKWidget
{
  Q_OBJECT

public:
  QvtkWidget(QWidget* parent = 0);
  virtual ~QvtkWidget();
  void drawAxissystem(void);
  public slots:
//  void drawDoublePoints(const double* const coords, const int number);
//  void addDoublePoint(const double* const coords);
//  void drawDblPtswNormals(const double* const coords, const double* const normals, const int number);
//  void drawPoints(const unsigned int number, const double* const coords, const double* const normals, const unsigned char* const colors);
//  void drawPoints(const std::vector<float>* const coords, const std::vector<float>* const normals);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZ>& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  void drawNormals(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals);
//  void drawPoints(const std::vector<Eigen::Vector3d>& coords, const std::vector<Eigen::Vector3d>* normals);
//  void addPoints(const unsigned int number, const double* const coords, const double* const normals, const unsigned char* const colors);
  void resetPoints(void);
  void drawPlanes(const std::vector<float>& origins, const float cellSize, const std::vector<float>& normals);
  void drawPlanes(const stdVecEig3f& points1, const stdVecEig3f& points2, const stdVecEig3f& centers ,const QColor& rgb);
  void drawOccuPancyGrid(const Eigen::Vector3d& ax0, const Eigen::Vector3d& ax1, const Eigen::Vector3d& ctr, const unsigned int cellsX, const unsigned int cellsY, const std::vector<int8_t>& data);
  void clearPlanes(void);
  void drawLines(void);
  void addLine(const Line& line){_lineVec.push_back(line);}
  void resetLines(void);
  void drawCropBox(const Eigen::Vector3d& pointMin, const Eigen::Vector3d& pointMax);
  void addCloud(const pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud){_clouds.push_back(cloud);}
  void addPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud);
  void addPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  void updateClouds(void);
  void clearClouds(void);//{_clouds.clear();}
  void setBackGround(const QColor& rgb);
  void drawCylinder(const Eigen::Vector3d& center, const float radius, const float height, const QColor& color, const unsigned int res);
  void clearArrow(void);
  void drawOrientatedArrow(const Eigen::Matrix4d& T);
  void drawCubeArray(const std::vector<QColor>& colors, const stdVecEig3d& centers, const double sizeCubes);  //todo: those cant probably not be removed...DO SMTH
  void newLines(const std::vector<Line>& lines);
protected:
  vtkSmartPointer<vtkRenderer>  _renderer;
private:
  vtkSmartPointer<vtkPolyData>  _pointPolyData;
  vtkSmartPointer<vtkPolyData>  _linePolyData;
  vtkSmartPointer<vtkPoints>    _points;
  vtkSmartPointer<vtkUnsignedCharArray> _pointColors;
  vtkSmartPointer<vtkDoubleArray> _pointNormals;
  vtkSmartPointer<vtkCellArray> _lines;
  vtkSmartPointer<vtkPoints>    _linepoints;
  std::vector<Line> _lineVec;
  std::vector<Line> _linesCropBox;
  std::vector<pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr > _clouds;
  vtkSmartPointer<vtkActor> _actorArrow;
};

}
#endif /* QVTKWIDGET_H_ */
