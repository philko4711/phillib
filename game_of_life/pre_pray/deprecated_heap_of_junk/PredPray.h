#ifndef PHILLIB_GAME_OF_LIFE_PREDPRAY_H_
#define PHILLIB_GAME_OF_LIFE_PREDPRAY_H_

#include "Food.h"
#include "IAgent.h"
#include "gui/MainWindow.h"
#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <memory>
#include <vector>

namespace phillib
{
namespace game_of_life
{
class PredPray : public QObject
{
  Q_OBJECT
public:
  PredPray();
  virtual ~PredPray() {}
  //void spawn(const IAgent::Agent& type, const QPoint& pos);
  void seedFoodRandom();
  bool setFoodPos(const QPointF& pos);

private slots:
  void                                  loopMain(); // TODO: thread
  private:
   //Map                                   _map;
  // std::vector<std::shared_ptr<IAgent> > _agents;
  // std::vector<std::shared_ptr<Food> >   _food;
  // std::vector<std::shared_ptr<IObjectMap> > _objectsMap;
  MainWindow                            _gui;
  QTimer _timerMain;
  std::vector<std::shared_ptr<IObjectMap> > _food;
};
} // namespace game_of_life
} // namespace phillib
#endif
