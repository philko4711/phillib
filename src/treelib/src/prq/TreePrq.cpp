#include "TreePrq.h"

namespace phillib
{
namespace treelib
{
TreePrq::TreePrq(const float lengthEdge, const float resolutionCell)
  {
  }

void TreePrg::push(std::vector<std::shared_ptr<IDataObject> >& dataNew)
{
  for(auto& iter : dataNew)
  {
    _tree = _tree->addData(iter);
  }
}


}
}
