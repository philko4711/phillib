#include "Leaf.h"
#include "Node.h"
#include "IDataObject.h"
#include <iostream>
namespace phillib
{
namespace treelib
{
Leaf::Leaf(const std::shared_ptr<RegionQ>& region):TreeObjectBase(region)
  {
    std::cout << __PRETTY_FUNCTION__ << "" << std::endl;
  }


std::shared_ptr<ITreeObject> Leaf::addData(std::shared_ptr<IDataObject>& data)
{
  std::cout << __PRETTY_FUNCTION__ << " adding data with index " << data->index().u() << " " << data->index().v() << std::endl;
  if(!this->inside(data->index()))
    return shared_from_this();
  if(this->empty())
  {  //empty leaf, store data
    _data = data;
    return shared_from_this();
  }
  else if(*data == *_data)
  {
    std::cout << __PRETTY_FUNCTION__ << " data object are too similar->apply merge " << std::endl;
    return shared_from_this();
  }
  std::shared_ptr<ITreeObject> node = std::make_shared<Node>(this->region());
  node->addData(data);
  node->addData(_data);
  return node;
}

void Leaf::print()
{
  std::cout << "Leaf";
  if(this->empty())
    std::cout << "(empty)" << std::endl;
  else
    std::cout << "(full)" << std::endl;

}

}
}
