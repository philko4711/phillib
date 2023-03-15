#ifndef PHILLIB_IMG_QUAD_SCENEIMGQUAD_H_
#define PHILLIB_IMG_QUAD_SCENEIMGQUAD_H_

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QImage>
#include <memory>

namespace phillib
{
namespace img_quad
{
  class SceneImgQuad : public QGraphicsScene
  {
    Q_OBJECT
    public:
    SceneImgQuad(QWidget* parent);
    virtual ~SceneImgQuad(){}
    void setImage(const std::shared_ptr<QImage>& image);//{_image = image;}
    protected:
      virtual void drawBackground(QPainter *painter, const QRectF &rect)override;
      private:
      std::shared_ptr<QImage> _image;
};
}
}
#endif

