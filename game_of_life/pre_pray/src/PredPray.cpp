#include "PredPray.h"
#include <QtCore/QDebug>
#include <phillib_utils/random.h>

#include "ObjectMap.h"

namespace phillib {
namespace game_of_life {
PredPray::PredPray() : _map(600, 600) {
  _gui.resize(600, 600);
  _gui.show();
  for (unsigned int i = 0; i < 10; i++)
    this->seedFoodRandom();
  connect(&_timerMain, SIGNAL(timeout()), this, SLOT(loopMain()));
  _timerMain.start(20);
}

void PredPray::seedFoodRandom() {
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

  std::vector<std::shared_ptr<IObjectMap>> mapObjects;
  qDebug() << __PRETTY_FUNCTION__ << "foood size " << _food.size();
  for (auto iter = _food.begin(); iter < _food.end(); iter++) {
    unsigned int amount = (*iter)->wither();
    if (amount <= 1) {
      qDebug() << __PRETTY_FUNCTION__ << "spread";
      for (int i = (*iter)->pos().y() - 1; i < (*iter)->pos().y() + 1; i++) {
        for (int j = (*iter)->pos().x() - 1; j < (*iter)->pos().x() + 1; j++) {
          qDebug() << __PRETTY_FUNCTION__ << "here";

          if ((i == (*iter)->pos().y()) || j == (*iter)->pos().x() || i < 0 ||
              j < 0 || i >= _map.sizeMap().y() || j >= _map.sizeMap().x())
            continue;
          auto ptr = std::make_shared<Food>(QPoint(j, i));
          _map.set(QPoint(j, i), ptr);
          mapObjects.push_back(ptr);
          _food.push_back(ptr);
        }
      }
      iter = _food.erase(iter);
    } else
      mapObjects.push_back(*iter);
  }
  for (auto &iter : _agents) {
    iter->iterate();
    mapObjects.push_back(std::dynamic_pointer_cast<IObjectMap>(iter));
  }
  _gui.updateMapObjects(mapObjects);
}
} // namespace game_of_life
} // namespace phillib
