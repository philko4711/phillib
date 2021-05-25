#ifndef HURENSOHN
#define HURENSOHN

#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


class vtkRenderer;
class vtkPolyData;
class vtkPoints;
class vtkUnsignedCharArray;
class vtkDoubleArray;
class vtkCellArray;

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
  void updatePlaneImage(vtkSmartPointer<vtkActor>& plane, const QImage& image);
  vtkSmartPointer<vtkActor>& actorPlaneImage(void){return _actorPlaneImage;}
private:
  vtkSmartPointer<vtkRenderer>          _renderer;
  vtkSmartPointer<vtkPolyData>          _pointPolyData;
  vtkSmartPointer<vtkPoints>            _points;
  vtkSmartPointer<vtkUnsignedCharArray> _pointColors;
  vtkSmartPointer<vtkDoubleArray>       _pointNormals;
  vtkSmartPointer<vtkActor> _actorPlaneImage;
};

#endif