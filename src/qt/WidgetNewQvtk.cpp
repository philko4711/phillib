#include "WidgetNewQvtk.h"
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkTransform.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkProperty.h>

WidgetNewQvtk::WidgetNewQvtk(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
    , _renderer(vtkRenderer::New())
    , _pointPolyData(vtkSmartPointer<vtkPolyData>::New())
    , _points(vtkSmartPointer<vtkPoints>::New())
    , _pointColors(vtkSmartPointer<vtkUnsignedCharArray>::New())
    , _pointNormals(vtkSmartPointer<vtkDoubleArray>::New())
{
vtkSmartPointer<vtkPolyDataMapper> pointMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  pointMapper->SetInputConnection(_pointPolyData->GetProducerPort());
#else
  pointMapper->SetInputData(_pointPolyData);
#endif

  //  pointMapper->SetInputConnection(_pointPolyData->GetProducerPort());

  vtkSmartPointer<vtkActor> pointActor = vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);
  pointActor->GetProperty()->SetPointSize(10);
  _renderer->AddActor(pointActor);

  _renderer->SetBackground(1.0, 1.0, 1.0);
  _renderer->GetActiveCamera()->Yaw(180);
  this->GetRenderWindow()->AddRenderer(_renderer);
}

void WidgetNewQvtk::addAxes()
{
  vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
  transform->Translate(0.0, 0.0, 0.0);

  vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();

  // The axes are positioned with a user transform
  axes->SetUserTransform(transform);

  // properties of the axes labels can be set as follows
  // this sets the x axis label to red
  // axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(
  //   colors->GetColor3d("Red").GetData());

  // the actual text of the axis label can be changed:
  // axes->SetXAxisLabelText("test");

  _renderer->AddActor(axes);
}

void WidgetNewQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>& cloud)
{
 _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName ("Colors");
  for(auto& iter : cloud.points)
  {
    _points->InsertNextPoint(iter.x, iter.y, iter.z);
    unsigned char temp[3];
    temp[0] = iter.r;
    temp[1] = iter.g;
    temp[2] = iter.b;
    colors->InsertNextTypedTuple(temp);
  }
  _pointPolyData->GetPointData()->SetScalars(colors);
  _pointPolyData->GetPointData()->SetNormals(NULL);
  _pointPolyData->SetPoints(_points);
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexFilter->SetInputConnection(polydata->GetProducerPort());
#else
  vertexFilter->SetInputData(_pointPolyData);
#endif
  vertexFilter->Update();
  _pointPolyData->ShallowCopy(vertexFilter->GetOutput());
  _points->Modified();
  this->update();
}

void WidgetNewQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZ>& cloud)
{
  _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName("Colors");
  for(auto& iter : cloud.points)
  {
    _points->InsertNextPoint(iter.x, iter.y, iter.z);
    unsigned char temp[3];
    temp[0] = 0;
    temp[1] = 0;
    temp[2] = 0;
    colors->InsertNextTypedTuple(temp);
  }
  _pointPolyData->GetPointData()->SetScalars(colors);
  _pointPolyData->GetPointData()->SetNormals(NULL);
  _pointPolyData->SetPoints(_points);
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexFilter->SetInputConnection(polydata->GetProducerPort());
#else
  vertexFilter->SetInputData(_pointPolyData);
#endif
  vertexFilter->Update();
  _pointPolyData->ShallowCopy(vertexFilter->GetOutput());
  _points->Modified();
  this->update();
}