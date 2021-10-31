#include "WidgetNewQvtk.h"
#include <QtCore/QByteArray>
#include <pcl/io/ply_io.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkImageImport.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkPlaneSource.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkTexture.h>
#include <vtkTextureMapToPlane.h>
#include <vtkTransform.h>
#include <vtkUnsignedCharArray.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkLineSource.h>
#include <vtkLine.h>
#include <vtkCellData.h>

#include <QtCore/QDebug>

// #include <vtkTextureMapToPlane.h>
// #include <vtkTexture.h>
#include <phillib_utils/random.h>
#include <vtkImageViewer2.h>
WidgetNewQvtk::WidgetNewQvtk(QWidget *parent)
    : QVTKOpenGLNativeWidget(parent), _renderer(vtkRenderer::New()),
      _pointPolyData(vtkSmartPointer<vtkPolyData>::New()),
      _points(vtkSmartPointer<vtkPoints>::New()),
      _pointColors(vtkSmartPointer<vtkUnsignedCharArray>::New()),
      _pointNormals(vtkSmartPointer<vtkDoubleArray>::New()),
      _lines(vtkSmartPointer<vtkCellArray>::New()),
      _linepoints(vtkSmartPointer<vtkPoints>::New()),
      _linePolyData(vtkSmartPointer<vtkPolyData>::New()) {
  vtkSmartPointer<vtkPolyDataMapper> pointMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  pointMapper->SetInputConnection(_pointPolyData->GetProducerPort());
#else
  pointMapper->SetInputData(_pointPolyData);
#endif

vtkSmartPointer<vtkPolyDataMapper> lineMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  pointMapper->SetInputConnection(_pointPolyData->GetProducerPort());
#else
  lineMapper->SetInputData(_linePolyData);
#endif

  //  pointMapper->SetInputConnection(_pointPolyData->GetProducerPort());

  _actorPoints = vtkSmartPointer<vtkActor>::New();
  _actorPoints->SetMapper(pointMapper);
  _actorPoints->GetProperty()->SetPointSize(10);
  _renderer->AddActor(_actorPoints);

  _actorLines= vtkSmartPointer<vtkActor>::New();
  _actorLines->SetMapper(lineMapper);
  _renderer->AddActor(_actorLines);

  _renderer->SetBackground(1.0, 1.0, 1.0);
  _renderer->GetActiveCamera()->Yaw(180);
  this->renderWindow()->AddRenderer(_renderer);
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
  _actorPoints->Modified();
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
    temp[0] = 255;
    temp[1] = 255;
    temp[2] = 255;
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

void WidgetNewQvtk::drawPoints(const std::string &pathPly) {
  pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::PLYReader reader;
  reader.read(pathPly, cloud);
  this->drawPoints(cloud);
  this->update();
}

void WidgetNewQvtk::addPlane(const Eigen::Vector3f &point0,
                             const Eigen::Vector3f &point1,
                             const Eigen::Vector3f &center,
                             const std::string &pathToImage) {
  // vtkNew<vtkNamedColors> colors;
  vtkNew<vtkPlaneSource> planeSource;
  planeSource->SetOrigin(center.x(), center.y(), center.z());
  planeSource->SetPoint1(point0.x(), point0.y(), point0.z());
  planeSource->SetPoint2(point1.x(), point1.y(), point1.z());
  planeSource->SetXResolution(959);
  planeSource->SetYResolution(1280);
  planeSource->Update();

  char color[10 * 10 * 3];
  std::vector<int> rs;
  std::vector<int> gs;
  std::vector<int> bs;

  phillib::utils::randomInts(10 * 10, rs, 0, 255);
  phillib::utils::randomInts(10 * 10, gs, 0, 255);
  phillib::utils::randomInts(10 * 10, bs, 0, 255);

  for (unsigned int i = 0; i < 10; i++) {
    for (unsigned int j = 0; j < 10; j++) {
      color[(i * 10 + j) * 3] = rs[i * 10 + j];
      color[(i * 10 + j) * 3 + 1] = gs[i * 10 + j];
      color[(i * 10 + j) * 3 + 2] = bs[i * 10 + j];
    }
  }

  vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
  vtkSmartPointer<vtkImageImport> imageImport =
      vtkSmartPointer<vtkImageImport>::New();
  imageImport->SetDataSpacing(1, 1, 1);
  imageImport->SetDataOrigin(0, 0, 0);
  imageImport->SetWholeExtent(0, 10 - 1, 0, 10 - 1, 0, 0);
  imageImport->SetDataExtentToWholeExtent();
  imageImport->SetDataScalarTypeToUnsignedChar();
  imageImport->SetNumberOfScalarComponents(3);
  imageImport->SetImportVoidPointer(color);
  imageImport->Update();
  texture->SetInputConnection(imageImport->GetOutputPort());
  // vtkSmartPointer<vtkTextureMapToPlane> texturePlane =
  //     vtkSmartPointer<vtkTextureMapToPlane>::New();
  // texturePlane->SetInputConnection(planeSource->GetOutputPort());

  // vtkNew<vtkImageReader2Factory> readerFactory;
  //   vtkSmartPointer<vtkImageReader2> textureFile;
  //   textureFile.TakeReference(readerFactory->CreateImageReader2(pathToImage.c_str()));
  //   textureFile->SetFileName(pathToImage.c_str());
  //   textureFile->Update();

  //   vtkNew<vtkTexture> atext;
  //   atext->SetInputConnection(textureFile->GetOutputPort());
  //   atext->InterpolateOn();

  vtkPolyData *plane = planeSource->GetOutput();
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputData(plane);
  mapper->SetScalarModeToUsePointFieldData();
  // mapper->SetInputConnection(texturePlane->GetOutputPort());
  vtkNew<vtkActor> actor;
  _actorPlaneImage = vtkSmartPointer<vtkActor>::New();
  _actorPlaneImage->SetMapper(mapper);
  // actor->SetTexture(atext);
  _actorPlaneImage->SetTexture(texture);
  // actor->GetProperty()->SetColor();
  _renderer->AddActor(_actorPlaneImage);
  this->update();
}

void WidgetNewQvtk::updatePlaneImage(vtkSmartPointer<vtkActor> &plane,
                                     QImage &image) {
  // char color[10 * 10 * 3];
  //   std::vector<int> rs;
  //   std::vector<int> gs;
  //   std::vector<int> bs;

  //   phillib::utils::randomInts(10 * 10, rs, 0, 255);
  //   phillib::utils::randomInts(10 * 10, gs, 0, 255);
  //   phillib::utils::randomInts(10 * 10, bs, 0, 255);

  //   for (unsigned int i = 0; i < 10; i++)
  //   {
  //     for (unsigned int j = 0; j < 10; j++)
  //     {
  //       color[(i * 10 + j) * 3] = rs[i * 10 + j];
  //       color[(i * 10 + j) * 3 + 1] = gs[i * 10 + j];
  //       color[(i * 10 + j) * 3 + 2] = bs[i * 10 + j];
  //     }
  //   }

  vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
  vtkSmartPointer<vtkImageImport> imageImport =
      vtkSmartPointer<vtkImageImport>::New();
  // QByteArray arry;
  // image.save(arry);
  imageImport->SetDataSpacing(1, 1, 1);
  imageImport->SetDataOrigin(0, 0, 0);
  imageImport->SetWholeExtent(0, (image.width() - 1), 0, (image.height() - 1),
                              0, 0);
  imageImport->SetDataExtentToWholeExtent();
  imageImport->SetDataScalarTypeToUnsignedChar();
  imageImport->SetNumberOfScalarComponents(4);
  imageImport->SetImportVoidPointer(image.bits());
  imageImport->Update();
  texture->SetInputConnection(imageImport->GetOutputPort());
  plane->SetTexture(texture);
  this->update();
}

void WidgetNewQvtk::clearPoints() {
  _pointPolyData->Reset();
  _points->Reset();
  _pointNormals->Reset();
  _pointNormals->Reset();
  _actorPoints->Modified();
}

void WidgetNewQvtk::clearPlanes() {}

void WidgetNewQvtk::clearLines() {
  _linepoints->Reset();
  _lines->Reset();
  _linePolyData->Reset();
  _lineVec.clear();
}

void WidgetNewQvtk::drawLines(void) 
{
  _linepoints->Reset();
  _lines->Reset();
  _linePolyData->Reset();
  unsigned int ctr = 0;
  vtkSmartPointer<vtkUnsignedCharArray> colors =
      vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  unsigned char black[3] = {0, 0, 0};
  unsigned char white[3] = {255, 255, 255};

  //std::cout << __PRETTY_FUNCTION__ << " start iterating " << std::endl;
  for(std::vector<Line>::iterator iter = _lineVec.begin(); iter != _lineVec.end(); iter++)
  {
    qDebug() << __PRETTY_FUNCTION__ << " color " << iter->_color;
    unsigned char color[3] = {iter->_color.red(), iter->_color.green(), iter->_color.blue()};

    color[0] = iter->_color.red();
    color[1] = iter->_color.green();
    color[2] = iter->_color.blue();
    double origin[3] = {0.0};
    double p0[3] = {0.0};
    //std::cout << __PRETTY_FUNCTION__ << " start end " << iter->_start << " " << iter->_end << std::endl;
    qDebug() << __PRETTY_FUNCTION__ << " color rgb " << color[0] << " " << color[1] << " " << color[2];
    for(unsigned int i = 0; i < 3; ++i)
    {
      origin[i] = static_cast<double>(iter->_start(i));
      p0[i] = static_cast<double>(iter->_end(i));
      //  std::cout << __PRETTY_FUNCTION__ << " " << origin[i] << " " << p0[i] << "\n";
    }
    _linepoints->InsertNextPoint(origin);
    _linepoints->InsertNextPoint(p0);
    vtkSmartPointer<vtkLine> lineVar = vtkSmartPointer<vtkLine>::New();

    lineVar->GetPointIds()->SetId(0,ctr++);
    lineVar->GetPointIds()->SetId(1,ctr++);
    _lines->InsertNextCell(lineVar);
    colors->InsertNextTypedTuple(color);
    // vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    // vtkSmartPointer<vtkPolyDataMapper> lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //actor->SetMapper(lineMapper);
    _actorLines->GetProperty()->SetLineWidth(iter->_width);
    //lineMapper->SetInputData(_linePolyData);
    // lineActors.push_back(actor);
    // lineMappers.push_back(lineMapper);

    //_renderer->AddActor(actor);

  }
  //  std::cout << __PRETTY_FUNCTION__ << " starting crooooo " << std::endl;
  //
  //  for(std::vector<Line>::iterator iter = _linesCropBox.begin(); iter != _linesCropBox.end(); iter++)
  //  {
  //    double origin[3] = {0.0};
  //    double p0[3] = {0.0};
  //    for(unsigned int i = 0; i < 3; ++i)
  //    {
  //      origin[i] = static_cast<double>(iter->_start(i));
  //      p0[i] = static_cast<double>(iter->_end(i));
  //      //  std::cout << __PRETTY_FUNCTION__ << " " << origin[i] << " " << p0[i] << "\n";
  //    }
  //    _linepoints->InsertNextPoint(origin);
  //    _linepoints->InsertNextPoint(p0);
  //    vtkSmartPointer<vtkLine> lineVar = vtkSmartPointer<vtkLine>::New();
  //    lineVar->GetPointIds()->SetId(0,ctr++);
  //    lineVar->GetPointIds()->SetId(1,ctr++);
  //
  //    _lines->InsertNextCell(lineVar);
  //  }
  // std::cout << __PRETTY_FUNCTION__ << " set this shi " << std::endl;

  _linePolyData->SetPoints(_linepoints);
  _linePolyData->SetLines(_lines);
  _linePolyData->GetCellData()->SetScalars(colors);
  _lines->Modified();
  _linepoints->Modified();
  _actorLines->Modified();

  this->update();
}