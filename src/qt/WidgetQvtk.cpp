/*
 * QvtkWidget.cpp
 *
 *  Created on: Aug 9, 2013
 *      Author: phil
 */


#include "WidgetQvtk.h"

#include <QtCore/QDebug>

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include "vtkProperty.h"
#include <vtkVertexGlyphFilter.h>
#include <vtkPolyDataMapper.h>
#include "vtkRenderWindow.h"
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkAxesActor.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkLine.h>
#include <vtkGlyph3D.h>
#include <vtkPlaneSource.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkTransform.h>
#include <vtkArrowSource.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkCubeSource.h>
#include <vtkGlyph3D.h>

#include <cstdlib>
#include <ctime>

namespace phillib
{
  namespace qt
  {

WidgetQvtk::WidgetQvtk(QWidget* parent) :
                                                           QVTKWidget(parent),
                                                           _renderer(vtkRenderer::New()),
                                                           _pointPolyData(vtkSmartPointer<vtkPolyData>::New()),
                                                          //  _glyphPolyData(vtkSmartPointer<vtkPolyData>::New()),
                                                          //  _linePolyData(vtkSmartPointer<vtkPolyData>::New()),
                                                           _points(vtkSmartPointer<vtkPoints>::New()),
                                                           _pointColors(vtkSmartPointer<vtkUnsignedCharArray>::New()),
                                                            _pointNormals(vtkSmartPointer<vtkDoubleArray>::New())
                                                          //  _lines(vtkSmartPointer<vtkCellArray>::New()),
                                                          //  _linepoints(vtkSmartPointer<vtkPoints>::New()),
                                                          //  _actorArrow(vtkSmartPointer<vtkActor>::New()),
                                                          //  _actorGlpyh(vtkSmartPointer<vtkActor>::New())

{
  vtkObject::GlobalWarningDisplayOff();
  _renderer->SetBackground(1.0, 1.0, 1.0);
  _renderer->GetActiveCamera()->Yaw(180);
  this->GetRenderWindow()->AddRenderer(_renderer);

  vtkSmartPointer<vtkPolyDataMapper> pointMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  pointMapper->SetInputConnection(_pointPolyData->GetProducerPort());
#else
  pointMapper->SetInputData(_pointPolyData);
#endif

  //  pointMapper->SetInputConnection(_pointPolyData->GetProducerPort());

  vtkSmartPointer<vtkActor> pointActor = vtkSmartPointer<vtkActor>::New();
  pointActor->SetMapper(pointMapper);
  pointActor->GetProperty()->SetPointSize(1);
  _renderer->AddActor(pointActor);
  // _pointNormals->SetNumberOfComponents(3); //3d normals (ie x,y,z)
  // _pointColors->SetNumberOfComponents(3);
  //_pointNormals->SetNumberOfTuples(number / 3);

  vtkSmartPointer<vtkPolyDataMapper> lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  //lineMapper->SetInputConnection(_linePolyData->GetProducerPort())
  ;
#else
  //lineMapper->SetInputData(_linePolyData)
  ;
#endif

  vtkSmartPointer<vtkActor> lineActor = vtkSmartPointer<vtkActor>::New();
  lineActor->SetMapper(lineMapper);
  //    // lineActor->GetProperty()->SetPointSize(1);
  _renderer->AddActor(lineActor);
  //  _renderer->ResetCamera();
  std::srand(std::time(NULL));

  vtkSmartPointer<vtkCamera> camera =
      vtkSmartPointer<vtkCamera>::New();
  camera->SetPosition(100, 0, 0);
  camera->SetFocalPoint(0, 0, 0);
  _renderer->SetActiveCamera(camera);
}

WidgetQvtk::~WidgetQvtk()
{

}

void WidgetQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud)
{
  _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName ("Colors");
  for(auto& iter : cloud->points)
  {
    _points->InsertNextPoint(iter.x, iter.y, iter.z);
    unsigned char temp[3];
    temp[0] = iter.r;
    temp[1] = iter.g;
    temp[2] = iter.b;
    colors->InsertNextTupleValue(temp);
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

void WidgetQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZRGB>& cloud)
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
    colors->InsertNextTupleValue(temp);
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

void WidgetQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZ>& cloud)
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
    temp[0] = 255;
    temp[1] = 255;
    temp[2] = 255;
    colors->InsertNextTupleValue(temp);
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

void WidgetQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud)
{
  _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName ("Colors");
  for(auto& iter : cloud->points)
  {
    _points->InsertNextPoint(iter.x, iter.y, iter.z);
    unsigned char temp[3];
    temp[0] = 255;
    temp[1] = 255;
    temp[2] = 255;
    colors->InsertNextTupleValue(temp);
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

void WidgetQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals)
{
  _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName ("Colors");

  vtkSmartPointer<vtkDoubleArray> pointNormalsArray = vtkSmartPointer<vtkDoubleArray>::New();
  pointNormalsArray->SetNumberOfComponents(3); //3d normals (ie x,y,z)
  pointNormalsArray->SetNumberOfTuples(cloud->size());

  //for(auto& iter : cloud->points)
  for(unsigned int i = 0; i < cloud->size(); i++)
  {
    _points->InsertNextPoint(cloud->points[i].x, cloud->points[i].z, cloud->points[i].z);
    unsigned char temp[3];
    temp[0] = 255;
    temp[1] = 255;
    temp[2] = 255;
    colors->InsertNextTupleValue(temp);
    if(std::isnan(normals->points[i].normal_x) ||std::isnan(normals->points[i].normal_y) || std::isnan(normals->points[i].normal_z))
      continue;
    double normal[3] = {normals->points[i].normal_x ,normals->points[i].normal_y, normals->points[i].normal_z};
    pointNormalsArray->SetTuple(i, normal) ;
  }
  _pointPolyData->GetPointData()->SetScalars(colors);
  _pointPolyData->GetPointData()->SetNormals(pointNormalsArray);
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

void WidgetQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr& cloud)
{
  _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName ("Colors");

  vtkSmartPointer<vtkDoubleArray> pointNormalsArray = vtkSmartPointer<vtkDoubleArray>::New();
  pointNormalsArray->SetNumberOfComponents(3); //3d normals (ie x,y,z)
  pointNormalsArray->SetNumberOfTuples(cloud->size());

  unsigned int i = 0;
  for(auto& iter : cloud->points)
    //for(unsigned int i = 0; i < cloud->size(); i++)
  {
    _points->InsertNextPoint(iter.x, iter.y, iter.z);
    unsigned char temp[3];
    temp[0] = iter.r;
    temp[1] = iter.g;
    temp[2] = iter.b;
    colors->InsertNextTupleValue(temp);

    double normal[3] = {iter.normal_x ,iter.normal_y, iter.normal_z};
    pointNormalsArray->SetTuple(i++, normal) ;
  }
  _pointPolyData->GetPointData()->SetScalars(colors);
  _pointPolyData->GetPointData()->SetNormals(pointNormalsArray);
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

void WidgetQvtk::drawPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud)
{
  if(!cloud.size())
    return;
  Eigen::Vector3f normal(cloud.begin()->normal_x, cloud.begin()->normal_y, cloud.begin()->normal_z);
  Eigen::Vector3i rgb(cloud.begin()->r, cloud.begin()->g, cloud.begin()->b);

  _pointPolyData->Reset();
  bool hasNormals = normal.norm() > 0.0;
  //bool hasRgb = rgb.norm() > 0;


  _pointPolyData->Reset();
  _points->Reset();
  vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();


  colors->SetNumberOfComponents(3);
  colors->SetName ("Colors");

  vtkSmartPointer<vtkDoubleArray> pointNormalsArray = vtkSmartPointer<vtkDoubleArray>::New();
  pointNormalsArray->SetNumberOfComponents(3); //3d normals (ie x,y,z)
  pointNormalsArray->SetNumberOfTuples(cloud.size());

  unsigned int i = 0;
  for(auto& iter : cloud.points)
    //for(unsigned int i = 0; i < cloud->size(); i++)
  {
    _points->InsertNextPoint(iter.x, iter.y, iter.z);
    if(hasNormals)
    {
      double nVar[3];
      nVar[0] = iter.normal_x;
      nVar[1] = iter.normal_y;
      nVar[2] = iter.normal_z;
      _pointNormals->InsertNextTuple(nVar);//     SetTuple(idCtr++, nVar);
    }

    unsigned char cVar[3] = {255};
//    if(hasRgb)
//    {
      cVar[0] = iter.r;
      cVar[1] = iter.g;
      cVar[2] = iter.b;
  //  }
    _pointColors->InsertNextTupleValue(cVar);

    colors->InsertNextTupleValue(cVar);

    double normal[3] = {iter.normal_x ,iter.normal_y, iter.normal_z};
    pointNormalsArray->SetTuple(i++, normal) ;
  }
  _pointPolyData->GetPointData()->SetScalars(colors);
  if(hasNormals)
      _pointPolyData->GetPointData()->SetNormals(pointNormalsArray);
    else
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

// void WidgetQvtk::drawNormals(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, const pcl::PointCloud<pcl::Normal>::Ptr& normals)
// {
//   if(cloud->size() != normals->size())
//   {
//     std::cout << __PRETTY_FUNCTION__ << " error! Cloud size differs normal size" << std::endl;
//   }
//   this->resetLines();
//   for(unsigned int i = 0; i < cloud->size(); i++)
//   {
//     if(std::isnan(normals->points[i].normal_x) ||std::isnan(normals->points[i].normal_y) || std::isnan(normals->points[i].normal_z))
//       continue;
//     this->addLine(Line(Eigen::Vector3d(cloud->points[i].x, cloud->points[i].y, cloud->points[i].z),
//         Eigen::Vector3d(normals->points[i].normal_x, normals->points[i].normal_y, normals->points[i].normal_z)));
//   }
//   std::cout << __PRETTY_FUNCTION__ << " will draw " << _lineVec.size() << " normals" << std::endl;
//   this->drawLines();
// }

// //void WidgetQvtk::addPoints(const unsigned int number, const double* const coords, const double* const normals, const unsigned char* const colors)
// //{
// //  //   qDebug() << __PRETTY_FUNCTION__ << "\n";
// //  //   if(colors == NULL)
// //  //      qDebug() << __PRETTY_FUNCTION__ << " no colors\n";
// //  unsigned int idCtr = 0;
// //  _pointPolyData->Reset();
// //  for(unsigned int i = 0; i < number; i += 3)
// //  {
// //    // qDebug() << __PRETTY_FUNCTION__ << " i = " << i << "\n";
// //    _points->InsertNextPoint(coords[i], coords[i + 1], coords[i + 2]);
// //    // qDebug() << __PRETTY_FUNCTION__ << " " << coords[i] << " " << coords[i + 1] << " " << coords[i + 2] << "\n";
// //    if(normals)
// //    {
// //      double nVar[3];
// //      nVar[0] = normals[i];
// //      nVar[1] = normals[i + 1];
// //      nVar[2] = normals[i + 2];
// //      _pointNormals->InsertNextTuple(nVar);//     SetTuple(idCtr++, nVar);
// //    }
// //    if(colors)
// //    {
// //      unsigned char cVar[3];
// //      cVar[0] = colors[i];
// //      cVar[1] = colors[i + 1];
// //      cVar[2] = colors[i + 2];
// //      _pointColors->InsertNextTupleValue(cVar);
// //    }
// //  }
// //  _pointPolyData->SetPoints(_points);
// //  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =  vtkSmartPointer<vtkVertexGlyphFilter>::New();
// //  glyphFilter->SetInputConnection(_pointPolyData->GetProducerPort());
// //  glyphFilter->Update();
// //  _pointPolyData->ShallowCopy(glyphFilter->GetOutput());
// //  if(colors)
// //    _pointPolyData->GetPointData()->SetScalars(_pointColors);
// //  if(normals)
// //    _pointPolyData->GetPointData()->SetNormals(_pointNormals);
// //  else
// //    _pointPolyData->GetPointData()->SetNormals(NULL);
// //  _points->Modified();
// //  //this->update();
// //}

// void WidgetQvtk::resetPoints(void)
// {
//   _pointPolyData->Reset();
//   _points->Reset();
//   _pointColors->Reset();
//   _pointNormals->Reset();
//   _points->Modified();
//   _pointColors->Modified();
//   _pointNormals->Modified();
//   this->update();
// }

// void WidgetQvtk::drawAxissystem(void)
// {
//   vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
//   axes->SetScale(2.0);
//   _renderer->AddActor(axes);
//   this->update();
// }

// void WidgetQvtk::drawPlanes(const std::vector<float>& origins, const float cellSize, const std::vector<float>& normals)
// {

// }

// void WidgetQvtk::clearPlanes(void)
// {

// }

// void WidgetQvtk::drawCropBox(const Eigen::Vector3d& pointMin, const Eigen::Vector3d& pointMax)
// {
//   _linesCropBox.clear();
//   std::cout << __PRETTY_FUNCTION__ << " 1 " << std::endl;
//   //@todo: need to clear the lines first before moving cropbox..but would delete all other lines...extra vec maybe?!
//   _linesCropBox.push_back(Line(pointMin, Eigen::Vector3d(pointMin(0), pointMax(1), pointMin(2))));
//   _linesCropBox.push_back(Line(pointMin, Eigen::Vector3d(pointMin(0), pointMin(1), pointMax(2))));
//   _linesCropBox.push_back(Line(pointMin, Eigen::Vector3d(pointMax(0), pointMin(1), pointMin(2))));
//   std::cout << __PRETTY_FUNCTION__ << " 2 " << std::endl;
//   _linesCropBox.push_back(Line(Eigen::Vector3d(pointMin(0), pointMax(1), pointMin(2)), Eigen::Vector3d(pointMin(0), pointMax(1), pointMax(2))));
//   _linesCropBox.push_back(Line(Eigen::Vector3d(pointMin(0), pointMax(1), pointMin(2)), Eigen::Vector3d(pointMax(0), pointMax(1), pointMin(2))));

//   _linesCropBox.push_back(Line(Eigen::Vector3d(pointMin(0), pointMin(1), pointMax(2)), Eigen::Vector3d(pointMin(0), pointMax(1), pointMax(2))));
//   _linesCropBox.push_back(Line(Eigen::Vector3d(pointMin(0), pointMin(1), pointMax(2)), Eigen::Vector3d(pointMax(0), pointMin(1), pointMax(2))));
//   std::cout << __PRETTY_FUNCTION__ << " 3 " << std::endl;
//   _linesCropBox.push_back(Line(pointMax, Eigen::Vector3d(pointMax(0), pointMin(1), pointMax(2))));
//   _linesCropBox.push_back(Line(pointMax, Eigen::Vector3d(pointMin(0), pointMax(1), pointMax(2))));
//   _linesCropBox.push_back(Line(pointMax, Eigen::Vector3d(pointMax(0), pointMax(1), pointMin(2))));
//   std::cout << __PRETTY_FUNCTION__ << " 4 " << std::endl;
//   _linesCropBox.push_back(Line(Eigen::Vector3d(pointMax(0), pointMin(1), pointMax(2)), Eigen::Vector3d(pointMax(0), pointMin(1), pointMin(2))));
//   _linesCropBox.push_back(Line(Eigen::Vector3d(pointMax(0), pointMin(1), pointMin(2)), Eigen::Vector3d(pointMax(0), pointMax(1), pointMin(2))));
//   std::cout << __PRETTY_FUNCTION__ << " 5 " << std::endl;
//   this->drawLines();
//   this->update();
// }

// void WidgetQvtk::drawLines(void)
// {
//   std::cout << __PRETTY_FUNCTION__ << "  " << std::endl;
//   _linepoints->Reset();
//   _lines->Reset();
//   _linePolyData->Reset();
//   std::cout << __PRETTY_FUNCTION__ << " resetted that shit " << std::endl;
//   unsigned int ctr = 0;
//   vtkSmartPointer<vtkUnsignedCharArray> colors =
//       vtkSmartPointer<vtkUnsignedCharArray>::New();
//   colors->SetNumberOfComponents(3);
//   unsigned char black[3] = {0, 0, 0};
//   unsigned char white[3] = {255, 255, 255};

//   //std::cout << __PRETTY_FUNCTION__ << " start iterating " << std::endl;
//   for(std::vector<Line>::iterator iter = _lineVec.begin(); iter != _lineVec.end(); iter++)
//   {
//     unsigned char color[3] = {iter->_color.red(), iter->_color.green(), iter->_color.blue()};
//     double origin[3] = {0.0};
//     double p0[3] = {0.0};
//     //std::cout << __PRETTY_FUNCTION__ << " start end " << iter->_start << " " << iter->_end << std::endl;
//     for(unsigned int i = 0; i < 3; ++i)
//     {
//       origin[i] = static_cast<double>(iter->_start(i));
//       p0[i] = static_cast<double>(iter->_end(i));
//       //  std::cout << __PRETTY_FUNCTION__ << " " << origin[i] << " " << p0[i] << "\n";
//     }
//     _linepoints->InsertNextPoint(origin);
//     _linepoints->InsertNextPoint(p0);
//     vtkSmartPointer<vtkLine> lineVar = vtkSmartPointer<vtkLine>::New();
//     lineVar->GetPointIds()->SetId(0,ctr++);
//     lineVar->GetPointIds()->SetId(1,ctr++);
//     _lines->InsertNextCell(lineVar);
//     colors->InsertNextTupleValue(color);
//   }
// //  std::cout << __PRETTY_FUNCTION__ << " starting crooooo " << std::endl;
// //
// //  for(std::vector<Line>::iterator iter = _linesCropBox.begin(); iter != _linesCropBox.end(); iter++)
// //  {
// //    double origin[3] = {0.0};
// //    double p0[3] = {0.0};
// //    for(unsigned int i = 0; i < 3; ++i)
// //    {
// //      origin[i] = static_cast<double>(iter->_start(i));
// //      p0[i] = static_cast<double>(iter->_end(i));
// //      //  std::cout << __PRETTY_FUNCTION__ << " " << origin[i] << " " << p0[i] << "\n";
// //    }
// //    _linepoints->InsertNextPoint(origin);
// //    _linepoints->InsertNextPoint(p0);
// //    vtkSmartPointer<vtkLine> lineVar = vtkSmartPointer<vtkLine>::New();
// //    lineVar->GetPointIds()->SetId(0,ctr++);
// //    lineVar->GetPointIds()->SetId(1,ctr++);
// //
// //    _lines->InsertNextCell(lineVar);
// //  }
//  // std::cout << __PRETTY_FUNCTION__ << " set this shi " << std::endl;
//   _linePolyData->SetPoints(_linepoints);
//   _linePolyData->SetLines(_lines);
//   _linePolyData->GetCellData()->SetScalars(colors);
//   _lines->Modified();
//   _linepoints->Modified();
//   this->update();
// //  std::cout << __PRETTY_FUNCTION__ << " nooooo " << std::endl;
// }

// void WidgetQvtk::resetLines(void)
// {
//   _lineVec.clear();
//   _linePolyData->Reset();
//   _linepoints->Reset();
//   _lines->Reset();
//   _linepoints->Modified();
//   _lines->Modified();
//   this->update();
// }

// void WidgetQvtk::updateClouds(void)
// {
//   //qDebug() << __PRETTY_FUNCTION__ << " drawing " << _clouds.size() << " clouds";
//   this->resetPoints();
//   for(auto& iter : _clouds)
//     this->addPoints(iter);
// }

// void WidgetQvtk::clearClouds(void)
// {
//   this->resetPoints();
//   _clouds.clear();
// }

// void WidgetQvtk::addPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud)
// {
//   //   qDebug() << __PRETTY_FUNCTION__ << "\n";
//   //   if(colors == NULL)
//   //      qDebug() << __PRETTY_FUNCTION__ << " no colors\n";
//   unsigned int idCtr = 0;
//   if(!cloud->size())
//     return;
//   Eigen::Vector3f normal(cloud->begin()->normal_x, cloud->begin()->normal_y, cloud->begin()->normal_z);
//   Eigen::Vector3i rgb(cloud->begin()->r, cloud->begin()->g, cloud->begin()->b);

//   _pointPolyData->Reset();
//   bool hasNormals = normal.norm() > 0.0;
//   //bool hasRgb = rgb.norm() > 0;

//   for(auto& iter : cloud->points)
//     //for(unsigned int i = 0; i < number; i += 3)
//   {
//     // qDebug() << __PRETTY_FUNCTION__ << " i = " << i << "\n";
//     _points->InsertNextPoint(iter.x, iter.y, iter.z);
//     if(hasNormals)
//     {
//       double nVar[3];
//       nVar[0] = iter.normal_x;
//       nVar[1] = iter.normal_y;
//       nVar[2] = iter.normal_z;
//       _pointNormals->InsertNextTuple(nVar);//     SetTuple(idCtr++, nVar);
//     }

//     unsigned char cVar[3] = {255};
// //    if(hasRgb)
// //    {
//       cVar[0] = iter.r;
//       cVar[1] = iter.g;
//       cVar[2] = iter.b;
//    // }
//     _pointColors->InsertNextTupleValue(cVar);
//   }
//   _pointPolyData->SetPoints(_points);
//   vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =  vtkSmartPointer<vtkVertexGlyphFilter>::New();
// #if VTK_MAJOR_VERSION <= 5
//   vertexFilter->SetInputConnection(polydata->GetProducerPort());
// #else
//   vertexFilter->SetInputData(_pointPolyData);
// #endif
//   vertexFilter->Update();
//   _pointPolyData->ShallowCopy(vertexFilter->GetOutput());
//   _pointPolyData->GetPointData()->SetScalars(_pointColors);
//   if(hasNormals)
//     _pointPolyData->GetPointData()->SetNormals(_pointNormals);
//   else
//     _pointPolyData->GetPointData()->SetNormals(NULL);
//   _points->Modified();
//   this->update();
// }

// void WidgetQvtk::addPoints(const pcl::PointCloud<pcl::PointXYZRGBNormal>& cloud)
// {
//   //   qDebug() << __PRETTY_FUNCTION__ << "\n";
//   //   if(colors == NULL)
//   //      qDebug() << __PRETTY_FUNCTION__ << " no colors\n";
//   unsigned int idCtr = 0;
//   _pointPolyData->Reset();
//   for(auto& iter : cloud.points)
//     //for(unsigned int i = 0; i < number; i += 3)
//   {
//     // qDebug() << __PRETTY_FUNCTION__ << " i = " << i << "\n";
//     _points->InsertNextPoint(iter.x, iter.y, iter.z);
//     //      if(normals)
//     //      {
//     //        double nVar[3];
//     //        nVar[0] = normals[i];
//     //        nVar[1] = normals[i + 1];
//     //        nVar[2] = normals[i + 2];
//     //        _pointNormals->InsertNextTuple(nVar);//     SetTuple(idCtr++, nVar);
//     //      }

//     unsigned char cVar[3];
//     cVar[0] = iter.r;
//     cVar[1] = iter.g;
//     cVar[2] = iter.b;
//     _pointColors->InsertNextTupleValue(cVar);
//   }
//   _pointPolyData->SetPoints(_points);
//   vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =  vtkSmartPointer<vtkVertexGlyphFilter>::New();
// #if VTK_MAJOR_VERSION <= 5
//   vertexFilter->SetInputConnection(polydata->GetProducerPort());
// #else
//   vertexFilter->SetInputData(_pointPolyData);
// #endif
//   vertexFilter->Update();
//   _pointPolyData->ShallowCopy(vertexFilter->GetOutput());
//   _pointPolyData->GetPointData()->SetScalars(_pointColors);
//   //    if(normals)
//   //      _pointPolyData->GetPointData()->SetNormals(_pointNormals);
//   //    else
//   _pointPolyData->GetPointData()->SetNormals(NULL);
//   _points->Modified();
//   this->update();
// }

// void WidgetQvtk::setBackGround(const QColor& rgb)
// {
//   _renderer->SetBackground(rgb.red(), rgb.green(), rgb.blue());
//   this->update();
// }

// void WidgetQvtk::drawCylinder(const Eigen::Vector3d& center, const float radius, const float height, const QColor& color, const unsigned int res)
// {
//   vtkSmartPointer<vtkCylinderSource> cylinderSource =
//       vtkSmartPointer<vtkCylinderSource>::New();
//   cylinderSource->SetCenter(center(0), center(1), center(2));
//   cylinderSource->SetRadius(radius);
//   cylinderSource->SetHeight(height);
//   cylinderSource->SetResolution(100);
//   //cylinderSource->

//   vtkSmartPointer<vtkPolyDataMapper> mapper =
//       vtkSmartPointer<vtkPolyDataMapper>::New();
//   mapper->SetInputConnection(cylinderSource->GetOutputPort());
//   vtkSmartPointer<vtkActor> actor =
//       vtkSmartPointer<vtkActor>::New();
//   actor->SetMapper(mapper);
//   actor->RotateX(90);
//   vtkSmartPointer<vtkTransform> transform =
//       vtkSmartPointer<vtkTransform>::New();

//   transform->Translate(0.0, 0, height / 2.0);
//   actor->SetUserTransform(transform);


//   _renderer->AddActor(actor);
//   this->update();
// }

// void WidgetQvtk::clearArrow(void)
// {
//   _renderer->RemoveActor(_actorArrow);
// }

// void WidgetQvtk::drawOrientatedArrow(const Eigen::Matrix4d& T)
// {
//   vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
//   //  transform->
//   vtkSmartPointer<vtkMatrix4x4> mat =
//       vtkSmartPointer<vtkMatrix4x4>::New();
//   for(unsigned int i = 0; i < 4; i++)
//   {
//     for(unsigned int j = 0; j < 4; j++)
//     {
//       mat->SetElement(i, j, T(i, j));
//     }
//   }
//   transform->SetMatrix(mat);
//   vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();

//   // Generate a random start and end point
//   double startPoint[3] = {0.0, 0.0, 0.0};
//   double endPoint[3] = {0.0, 0.0, 0.0};

//   vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
//       vtkSmartPointer<vtkTransformPolyDataFilter>::New();
//   transformPD->SetTransform(transform);
//   transformPD->SetInputConnection(arrowSource->GetOutputPort());

//   vtkSmartPointer<vtkPolyDataMapper> mapper =
//       vtkSmartPointer<vtkPolyDataMapper>::New();

//   mapper->SetInputConnection(transformPD->GetOutputPort());
//   _actorArrow->SetMapper(mapper);

//   _renderer->AddActor(_actorArrow);

//   //  vtkTransform tf;
//   //  tf.SetM
// }

// void WidgetQvtk::drawCubeArray(const std::vector<QColor>& colorVec, const stdVecEig3d& centerVec, const double sizeCubes)
// {
//   this->clearCubeArray();
//   if(colorVec.size() != centerVec.size())
//   {
//     std::cout << __PRETTY_FUNCTION__ << " error! Point / color vector sizes differ " << std::endl;
//     return;
//   }
//   vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//   vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
//   colors->SetName("colors");
//   colors->SetNumberOfComponents(3);
// //  unsigned char r[3] = {255,0,0};
// //  unsigned char g[3] = {0,255,0};
// //  unsigned char b[3] = {0,0,255};
//   for(unsigned int i = 0; i < colorVec.size(); i++)
//   {
//     const unsigned char rgb[3] = {static_cast<unsigned char>(colorVec[i].red()), static_cast<unsigned char>(colorVec[i].green()),
//         static_cast<unsigned char>(colorVec[i].blue())};
//     colors->InsertNextTupleValue(rgb);
//     points->InsertNextPoint(centerVec[i].x(), centerVec[i].y(), centerVec[i].z());
//   }
// //  vtkSmartPointer<vtkPolyData> polydata =
// //      vtkSmartPointer<vtkPolyData>::New();
//   _glyphPolyData->SetPoints(points);
//   _glyphPolyData->GetPointData()->SetScalars(colors);

//   // Create anything you want here, we will use a cube for the demo.
//   vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
//   cubeSource->SetXLength(sizeCubes);
//   cubeSource->SetYLength(sizeCubes);
//   cubeSource->SetZLength(sizeCubes);

//   vtkSmartPointer<vtkGlyph3D> glyph3D =
//       vtkSmartPointer<vtkGlyph3D>::New();
//   glyph3D->SetColorModeToColorByScalar();
//   glyph3D->SetSourceConnection(cubeSource->GetOutputPort());
// #if VTK_MAJOR_VERSION <= 5
//   glyph3D->SetInput(_glyphPolyData);
// #else
//   glyph3D->SetInputData(_glyphPolyData);
// #endif
//   glyph3D->ScalingOff();
//   glyph3D->Update();



//   // Create a mapper and actor
//   vtkSmartPointer<vtkPolyDataMapper> mapper =
//       vtkSmartPointer<vtkPolyDataMapper>::New();
//   mapper->SetInputConnection(glyph3D->GetOutputPort());
//   //vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//   _actorGlpyh->SetMapper(mapper);
//   _renderer->AddActor(_actorGlpyh);
//   this->update();
// }

// void WidgetQvtk::clearCubeArray(void)
// {
//   _glyphPolyData->Reset();
//   _renderer->RemoveActor(_actorGlpyh);
//   this->update();
// }

}
}