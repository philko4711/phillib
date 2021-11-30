#ifndef PHILLIB_GAME_OF_LIFE_IAGENT_H_
#define PHILLIB_GAME_OF_LIFE_IAGENT_H_



namespace phillib
{
namespace game_of_life
{
  class IAgent
  {
    public:
    enum class TypeAgent
    {
      Prey=0,
      Predator,
      Food       //TODO: maybe add subclasses for passive and active agents or find a better definition for food and seed
    };
    IAgent(){}
    virtual ~IAgent(){}
    virtual void iterate()=0;
};
}
}
#endif

