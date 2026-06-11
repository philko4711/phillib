#include "EffectBase.h"
#include "IEffect.h"

namespace phillib
{

namespace arduino
{    
    
IEffect::TypeEffect EffectBase::stringToTypeEffect(const String& effect)
{
    if(effect == "breathe")
    {
        return IEffect::TypeEffect::BREATHE;
    }
    else if(effect == "wanderingPixl")
    {
        return IEffect::TypeEffect::WANDERING_PXL;
    }
    else if(effect == "expand")
    {
          return IEffect::TypeEffect::EXPAND;
    }
    else if(effect == "pacifica")
    {
          return IEffect::TypeEffect::PACIFICA;
    }
    else
        return IEffect::TypeEffect::ERROR;
}

}

}