#ifndef PHILLIB_GAME_OF_LIFE_IOBJECTMAP_H_
#define PHILLIB_GAME_OF_LIFE_IOBJECTMAP_H_

namespace phillib
{
namespace game_of_life
{
class IObjectMap
{
public:
  IObjectMap();
  virtual ~IObjectMap();
  virtual void iterate();
  /**
   * @brief Abstract method. Mapobjects return their health in percentage. [0, 100]
   * 
   * @return * uint8_t Health
   */
  virtual uint8_t health(void)const=0;
};
} // namespace game_of_life
} // namespace phillib
#endif
