#include "SceneImgQuad.h"

namespace phillib
{
namespace img_quad
{
SceneImgQuad::SceneImgQuad(QWidget* parent)
    : QGraphicsScene(parent)
{
}

void SceneImgQuad::drawBackground(QPainter* painter, const QRectF& rect) {}
} // namespace img_quad
} // namespace phillib
