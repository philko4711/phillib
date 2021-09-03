#include "Map.h"

namespace phillib {
namespace game_of_life {
Map::Map(const unsigned int height, const unsigned int width):_map(height * width), _sizeMap(QPoint(0, 0), QSize(height, width)) {}

} // namespace game_of_life
} // namespace phillib
