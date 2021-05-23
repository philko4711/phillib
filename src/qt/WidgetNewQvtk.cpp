#include "WidgetNewQvtk.h"
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPlaneSource.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkTransform.h>
#include <vtkUnsignedCharArray.h>
#include <vtkImageImport.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkTexture.h>

// #include <vtkTextureMapToPlane.h>
// #include <vtkTexture.h>
#include <vtkImageViewer2.h>
#include <phillib_utils/random.h>
WidgetNewQvtk::WidgetNewQvtk(QWidget *parent)
    : QVTKOpenGLNativeWidget(parent), _renderer(vtkRenderer::New()),
      _pointPolyData(vtkSmartPointer<vtkPolyData>::New()),
      _points(vtkSmartPointer<vtkPoints>::New()),
      _pointColors(vtkSmartPointer<vtkUnsignedCharArray>::New()),
      _pointNormals(vtkSmartPointer<vtkDoubleArray>::New()) {
  vtkSmartPointer<vtkPolyDataMapper> pointMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
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

  _renderer->SetBackground(0.0, 0.0, 0.0);
  _renderer->GetActiveCamera()->Yaw(180);
  this->GetRenderWindow()->AddRenderer(_renderer);
}

void WidgetNewQvtk::addAxes() {
  vtkSmartPointer<vtkTransform> transform =
      vtkSmartPointer<vtkTransform>::New();
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

void WidgetNewQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZRGB> &cloud) {
  _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors =
      vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName("Colors");
  for (auto &iter : cloud.points) {
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
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
      vtkSmartPointer<vtkVertexGlyphFilter>::New();
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

void WidgetNewQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZ> &cloud) {
  _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors =
      vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName("Colors");
  for (auto &iter : cloud.points) {
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
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
      vtkSmartPointer<vtkVertexGlyphFilter>::New();
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

void WidgetNewQvtk::addPlane(const Eigen::Vector3f &point0,
                             const Eigen::Vector3f &point1,
                             const Eigen::Vector3f &center) {
                               //vtkNew<vtkNamedColors> colors;
  vtkNew<vtkPlaneSource> planeSource;
  planeSource->SetOrigin(center.x(), center.y(), center.z());
  planeSource->SetPoint1(point0.x(), point0.y(), point0.z());
  planeSource->SetPoint2(point1.x(), point1.y(), point1.z());
  planeSource->SetXResolution(10);
  planeSource->SetYResolution(10);
  planeSource->Update();
  
  char color[10 * 10 * 3];
  std::vector<int> rs;
  std::vector<int> gs;
  std::vector<int> bs;

  
  phillib::utils::randomInts(10 * 10, rs, 0, 255);
  phillib::utils::randomInts(10 * 10, gs, 0, 255);
  phillib::utils::randomInts(10 * 10, bs, 0, 255);

  
  for (unsigned int i = 0; i < 10; i++)
  {
    for (unsigned int j = 0; j < 10; j++)
    {
      color[(i * 10 + j) * 3] = rs[i * 10 + j];
      color[(i * 10 + j) * 3 + 1] = gs[i * 10 + j];    
      color[(i * 10 + j) * 3 + 2] = bs[i * 10 + j];
    }

  }
 
vtkNew<vtkImageReader2Factory> readerFactory;
  vtkSmartPointer<vtkImageReader2> textureFile;
  textureFile.TakeReference(readerFactory->CreateImageReader2("/home/phil/Pictures/dicpr.jpeg"));
  textureFile->SetFileName("/home/phil/Pictures/dicpr.jpeg");
  textureFile->Update();

  vtkNew<vtkTexture> atext;
  atext->SetInputConnection(textureFile->GetOutputPort());
  atext->InterpolateOn();

 


  vtkPolyData *plane = planeSource->GetOutput();
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputData(plane);
  mapper->SetScalarModeToUsePointFieldData();
   mapper->SelectColorArray(color);
  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  actor->SetTexture(atext);
  //actor->GetProperty()->SetColor();
  _renderer->AddActor(actor);
  this->update();
}