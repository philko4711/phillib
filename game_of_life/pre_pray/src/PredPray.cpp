#include "PredPray.h"
#include <phillib_utils/random.h>

namespace phillib {
namespace game_of_life {
PredPray::PredPray() : _map(600, 600) {
  _gui.resize(600, 600);
  _gui.show();
}

void PredPray::seedFoodRandom() {
  const QRect &sizeMap = _map.sizeMap();
  std::vector<int> valsX;
  phillib::utils::randomInts(1, valsX, sizeMap.topLeft().x(), sizeMap.width());
  std::vector<int> valsY;
  phillib::utils::randomInts(1, valsY, sizeMap.topLeft().y(), sizeMap.height());
  const QPoint pos(*valsX.begin(), *valsY.begin());
  auto ptr = std::make_shared<Food>();
  _map.set(pos, ptr);
  _food.push_back(ptr);
  qDebug() << __PRETTY_FUNCTION__ << " creating food at " << pos;
}

void PredPray::loopMain() {
  for (auto &iter : _food)
    iter->wither();
  for (auto &iter : _agents)
    iter->iterate();
}
} // namespace game_of_life
} // namespace phillib
