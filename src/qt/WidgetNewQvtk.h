#ifndef HURENSOHN
#define HURENSOHN

#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <QtGui/QColor>


class vtkRenderer;
class vtkPolyData;
class vtkPoints;
class vtkUnsignedCharArray;
class vtkDoubleArray;
class vtkCellArray;
//class vtkCubeSource;

struct Line
{
  Line():
    _color(Qt::black),
    _width(1.0)
  {}
  Line(const Eigen::Vector3f& start, const Eigen::Vector3f& end):
    _start(start),
    _end(end),
    _color(Qt::black),
    _width(1.0)
    {}
  Line(const pcl::PointXYZ& start, const pcl::PointXYZ& end):
    _start(Eigen::Vector3f(static_cast<double>(start.x), static_cast<double>(start.y), static_cast<double>(start.z))),
    _end(Eigen::Vector3f(static_cast<double>(end.x), static_cast<double>(end.y), static_cast<double>(end.z))),
    _color(Qt::black),
    _width(1.0)
    {}
  Eigen::Vector3f _start;
  Eigen::Vector3f _end;
  QColor _color;
  float _width;
};

class WidgetNewQvtk : public QVTKOpenGLNativeWidget
{
public:
  WidgetNewQvtk(QWidget* parent = nullptr);
  virtual ~WidgetNewQvtk() {}
  void addAxes();  
  //void drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZ>& cloud);
  void drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>& cloud);
  void drawPoints(const std::string& pathPly);
  void addPlane(const Eigen::Vector3f& point0, const Eigen::Vector3f& point1, const Eigen::Vector3f& center, const std::string& pathToImage);
  void addCube(const Eigen::Vector3f& dim, const Eigen::Vector3f& center);
  void drawCubes();

  void updatePlaneImage(vtkSmartPointer<vtkActor>& plane, QImage& image);
  vtkSmartPointer<vtkActor>& actorPlaneImage(void){return _actorPlaneImage;}
  void drawLines(void);
  void addLine(const Line& line){_lineVec.push_back(line);}
  void clearLines(void);
  void clearPoints();
  void clearPlanes();
  void clearCubes();//{_actorsCubes.clear();}
private:
  vtkSmartPointer<vtkRenderer>          _renderer;
  vtkSmartPointer<vtkPolyData>          _pointPolyData;
  vtkSmartPointer<vtkPoints>            _points;
  vtkSmartPointer<vtkUnsignedCharArray> _pointColors;
  vtkSmartPointer<vtkDoubleArray>       _pointNormals;
  vtkSmartPointer<vtkCellArray> _lines;
  vtkSmartPointer<vtkPoints>    _linepoints;
  vtkSmartPointer<vtkPolyData>  _linePolyData;
  std::vector<Line> _lineVec;
  vtkSmartPointer<vtkActor> _actorPlaneImage;
  vtkSmartPointer<vtkActor> _actorPoints;
  vtkSmartPointer<vtkActor> _actorLines;
  std::vector<vtkSmartPointer<vtkActor> > _actorsCubes;
};

#endif