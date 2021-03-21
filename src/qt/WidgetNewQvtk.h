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
private:
  vtkSmartPointer<vtkRenderer>          _renderer;
  vtkSmartPointer<vtkPolyData>          _pointPolyData;
  vtkSmartPointer<vtkPoints>            _points;
  vtkSmartPointer<vtkUnsignedCharArray> _pointColors;
  vtkSmartPointer<vtkDoubleArray>       _pointNormals;
};

#endif