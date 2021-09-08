#include "PredPray.h"
#include <phillib_utils/random.h>
#include <QtCore/QDebug>

#include "ObjectMap.h"

namespace phillib {
namespace game_of_life {
PredPray::PredPray() : _map(600, 600) {
  _gui.resize(600, 600);
  _gui.show();
  for(unsigned int i =0; i < 10; i++)
    this->seedFoodRandom();
  connect(&_timerMain, SIGNAL(timeout()), this, SLOT(loopMain()));  
  _timerMain.start(20);
}

void PredPray::seedFoodRandom() 
{
  const QRect &sizeMap = _map.sizeMap();
  std::vector<int> valsX;
  phillib::utils::randomInts(1, valsX, sizeMap.topLeft().x(), sizeMap.width());
  std::vector<int> valsY;
  phillib::utils::randomInts(1, valsY, sizeMap.topLeft().y(), sizeMap.height());
  const QPoint pos(*valsX.begin(), *valsY.begin());
  auto ptr = std::make_shared<Food>(pos);
  _map.set(pos, ptr);
  _food.push_back(ptr);
  qDebug() << __PRETTY_FUNCTION__ << " creating food at " << pos;
}

void PredPray::loopMain() {
  qDebug() << __PRETTY_FUNCTION__ << "entry";
  std::vector<std::shared_ptr<IObjectMap> > mapObjects;
  for (auto &iter : _food)
  {
    iter->wither();
    mapObjects.push_back(iter);
  }
  for (auto &iter : _agents)
  {
    iter->iterate();
    mapObjects.push_back(std::dynamic_pointer_cast<IObjectMap>(iter));
  }
  qDebug() << __PRETTY_FUNCTION__ << " Gui will draw " << mapObjects.size() << " objects";
  _gui.updateMapObjects(mapObjects);
}
} // namespace game_of_life
} // namespace phillib
