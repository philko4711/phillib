#include "Node.h"
#include "IDataObject.h"
#include "RegionQ.h"
namespace phillib
{
namespace treelib
{
Node::Node(const RegionQ& region):TreeObjectBase(region) 
{
  //todo: this constructor should split the given region / 4 -> methd in RegionQ

}

std::shared_ptr<ITreeObject> Node::addData(std::shared_ptr<IDataObject>& data)
{
  const Index& idx = data->index();
  for(unsigned int i = static_cast<unsigned int>(Node::Succ::TL); i <= static_cast<unsigned int>(Node::Succ::BR); i++)
    if(successors[i]->inside(idx))
      successors[i]->addData(data);
  return shared_from_this();    
}

} // namespace treelib
} // namespace phillib
