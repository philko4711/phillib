/*
 * QvtkWidget.h
 *
 *  Created on: Aug 9, 2013
 *      Author: phil
 */

#ifndef QVTKWIDGET_H_
#define QVTKWIDGET_H_

#include <QVTKWidget.h>
#include <QtGui/QColor>
#include <vector>

#include <vtkActor.h>
#include <vtkSmartPointer.h>

#include <string>
#include <vector>

#include <Eigen/Dense>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <phillib_utils/typedefs_eigen.h>

class vtkRenderer;
class vtkPolyData;
class vtkPoints;
class vtkUnsignedCharArray;
class vtkDoubleArray;
class vtkCellArray;

namespace phillib // TODO: Move the class to the phillib_qt lib and change this namespace
{

namespace qt
{

struct Line
{
  Line(const Eigen::Vector3d& start, const Eigen::Vector3d& end)
      : _start(start)
      , _end(end)
      , _color(Qt::white)
  {
  }
  Line(const pcl::PointXYZ& start, const pcl::PointXYZ& end)
      : _start(Eigen::Vector3d(static_cast<double>(start.x), static_cast<double>(start.y), static_cast<double>(start.z)))
      , _end(Eigen::Vector3d(static_cast<double>(end.x), static_cast<double>(end.y), static_cast<double>(end.z)))
      , _color(Qt::white)
  {
  }
  Eigen::Vector3d _start;
  Eigen::Vector3d _end;
  QColor          _color;
};
class WidgetQvtk : public QVTKWidget
{
  Q_OBJECT

public:
  WidgetQvtk(QWidget* parent = 0);
  virtual ~WidgetQvtk();
  void drawAxissystem(void);
public slots:
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZ>& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  void resetPoints(void);
  // void drawPlanes(const std::vector<float>& origins, const float cellSize, const std::vector<float>& normals);
  // void clearPlanes(void);
  // void drawLines(void);
  // void addLine(const Line& line) { _lineVec.push_back(line); }
  // void resetLines(void);
  // void drawCropBox(const Eigen::Vector3d& pointMin, const Eigen::Vector3d& pointMax);
  // void addCloud(const pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud) { _clouds.push_back(cloud); }
  // void addPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud);
  // void addPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud);
  // void updateClouds(void);
  // void clearClouds(void); //{_clouds.clear();}
  // void setBackGround(const QColor& rgb);
  // void drawCylinder(const Eigen::Vector3d& center, const float radius, const float height, const QColor& color, const unsigned int res);
  // void clearArrow(void);
  // void drawOrientatedArrow(const Eigen::Matrix4d& T);
  // void drawCubeArray(const std::vector<QColor>& colors, const stdVecEig3d& centers,
  //                    const double sizeCubes); // todo: those cant probably not be removed...DO SMTH
  // void clearCubeArray(void);

protected:
  vtkSmartPointer<vtkRenderer> _renderer;

private:
  vtkSmartPointer<vtkPolyData>                              _pointPolyData;
  // vtkSmartPointer<vtkPolyData>                              _glyphPolyData;
  // vtkSmartPointer<vtkPolyData>                              _linePolyData;
  vtkSmartPointer<vtkPoints>                                _points;
  vtkSmartPointer<vtkUnsignedCharArray>                     _pointColors;
   vtkSmartPointer<vtkDoubleArray>                           _pointNormals;
  // vtkSmartPointer<vtkCellArray>                             _lines;
  // vtkSmartPointer<vtkPoints>                                _linepoints;
  // std::vector<Line>                                         _lineVec;
  // std::vector<Line>                                         _linesCropBox;
  // std::vector<pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr> _clouds;
  // vtkSmartPointer<vtkActor>                                 _actorArrow;
  // vtkSmartPointer<vtkActor>                                 _actorGlpyh;
};

} // namespace phros_traversability
}
#endif /* QVTKWIDGET_H_ */
