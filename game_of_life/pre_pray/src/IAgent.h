#ifndef PHILLIB_GAME_OF_LIFE_IAGENT_H_
#define PHILLIB_GAME_OF_LIFE_IAGENT_H_



namespace phillib
{
namespace game_of_life
{
  class IAgent
  {
    public:
    IAgent();
    virtual ~IAgent();
    virtual void iterate()=0;
};
}
}
#endif

