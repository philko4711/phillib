#include "Leaf.h"
#include "Node.h"

namespace phillib
{
namespace treelib
{
Leaf::Leaf(const RegionQ& region):TreeObjectBase(region)
  {
  }


std::shared_ptr<ITreeObject> Leaf::addData(std::shared_ptr<IDataObject>& data)
{
  if(this->empty())
  {  //empty leaf, store data
    _data = data;
    return shared_from_this();
  }
  //else if(//todo: implement operator==)
  std::shared_ptr<ITreeObject> node = std::make_shared<Node>();
}

}
}
