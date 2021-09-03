#include "PredPray.h"
#include <phillib_utils/random.h>

namespace phillib {
namespace game_of_life {
PredPray::PredPray() {}

void PredPray::seedFoodRandom()
{
  const QRect& sizeMap = _map.sizeMap();
  std::vector<int> valsX;
  phillib::utils::randomInts(1, valsX, sizeMap.topLeft().x(), sizeMap.width());
  std::vector<int> valsY;
  phillib::utils::randomInts(1, valsY, sizeMap.topLeft().y(), sizeMap.height());
}

void PredPray::loopMain() {
  for (auto &iter : _food)
    iter->wither();
  for (auto &iter : _agents)
    iter->iterate();
}
} // namespace game_of_life
} // namespace phillib
