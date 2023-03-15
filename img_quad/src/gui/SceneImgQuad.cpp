#include "SceneImgQuad.h"
#include <QtGui/QPainter>
#include <iostream>
namespace phillib
{
namespace img_quad
{
SceneImgQuad::SceneImgQuad(QWidget* parent)
    : QGraphicsScene(parent)
{
}

void SceneImgQuad::drawBackground(QPainter* painter, const QRectF& rect) 
{
    if(!_image)
        return;
    std::cout << __PRETTY_FUNCTION__ << "" << std::endl;

    painter->drawImage(this->sceneRect(), *_image, _image->rect());
}

void SceneImgQuad::setImage(const std::shared_ptr<QImage>& image)
{
    this->setSceneRect(image->rect());
    _image = image;
    //this->update();
    }

} // namespace img_quad
} // namespace phillib
