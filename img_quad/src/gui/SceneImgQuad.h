#ifndef PHILLIB_IMG_QUAD_SCENEIMGQUAD_H_
#define PHILLIB_IMG_QUAD_SCENEIMGQUAD_H_

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsScene>

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
    protected:
      virtual void drawBackground(QPainter *painter, const QRectF &rect)override;
};
}
}
#endif

