#include "TreePrq.h"
#include "ITreeObject.h"
#include "Leaf.h"
namespace phillib
{
namespace treelib
{
TreePrq::TreePrq(const float lengthEdge, const float resolutionCell)
  {
  }

void TreePrq::push(std::vector<std::shared_ptr<IDataObject> >& dataNew)
{
  for(auto& iter : dataNew)
  {
    _tree = _tree->addData(iter);
  }
}

const bool TreePrq::empty(void)const
{
  if(_tree->type() == ITreeObject::Type::NODE)
    return false;
  return std::dynamic_pointer_cast<Leaf>(_tree)->empty();  
}

}
}
