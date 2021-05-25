#ifndef PHILLIB_QT_IMAGEMAGIC_H_
#define PHILLIB_QT_IMAGEMAGIC_H_

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGui/QImage>
#include "WidgetNewQvtk.h"
#include "MenuTransform.h"
#include <memory>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>

namespace phillib
{
namespace qt
{
  class ImageMagic : public QObject
  {
    Q_OBJECT
    public:
    ImageMagic(const std::string& pathToImage, const std::string& pathToPcl);
    ImageMagic();
    virtual ~ImageMagic(){}
    public slots:
      void callBackTimer();
      void transformChanged();
    private:
    void backProject();
      WidgetNewQvtk _viewer;
      QTimer _timer;
      MenuTransform _menuTransform;
      std::unique_ptr<pcl::PointCloud<pcl::PointXYZ> > _pcl;
      QImage _imageCamera;
};
}
}
#endif

