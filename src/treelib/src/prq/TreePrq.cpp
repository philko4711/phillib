#include "TreePrq.h"
#include "ITreeObject.h"
#include "Leaf.h"
#include "RegionQ.h"
namespace phillib
{
namespace treelib
{
TreePrq::TreePrq(const float lengthEdge, const float resolutionCell):_res(resolutionCell)
  {
    auto regionInitial = std::make_shared<RegionQ>(Index(0, 0), 2048); //toDO: this is only for testing. The real initial region will be a parameter
    _tree = std::make_shared<Leaf>(regionInitial); 
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
