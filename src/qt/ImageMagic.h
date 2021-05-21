#ifndef PHILLIB_QT_IMAGEMAGIC_H_
#define PHILLIB_QT_IMAGEMAGIC_H_

#include <QtCore/QObject>
#include "WidgetNewQvtk.h"

namespace phillib
{
namespace qt
{
  class ImageMagic : public QObject
  {
    public:
    ImageMagic();
    virtual ~ImageMagic(){}
    private:
      WidgetNewQvtk _viewer;
};
}
}
#endif

