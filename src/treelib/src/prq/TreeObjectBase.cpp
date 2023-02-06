#include "TreeObjectBase.h"

namespace phillib
{
namespace treelib
{
TreeObjectBase::TreeObjectBase(const std::shared_ptr<RegionQ>& region):_region(region)
  {
  }

bool TreeObjectBase::inside(const Index& index)const
{
  Index idxMin  = this->region()->tl();
  Index idxMax  = idxMin + Index(this->region()->lengthEdge(), this->region()->lengthEdge());
  return ((index > idxMin) && (index < idxMax));
  }  
// const std::shared_ptr<RegionQ>& TreeObjectBase::region()const
// {
  
// }

}
}
