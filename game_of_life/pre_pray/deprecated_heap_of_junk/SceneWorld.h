#ifndef PHILLIB_GAME_OF_LIFE_SCENEWORLD_H_
#define PHILLIB_GAME_OF_LIFE_SCENEWORLD_H_


#include <QtWidgets/QGraphicsScene>

namespace phillib
{
namespace game_of_life
{
  class SceneWorld : public QGraphicsScene
  {
    Q_OBJECT
    SceneWorld(QObject* parent = nullptr);
    virtual ~SceneWorld(){}
};
}
}
#endif

