#ifndef PHILLIB_TREELIB_TREEOBJECTBASE_H_
#define PHILLIB_TREELIB_TREEOBJECTBASE_H_

#include "ITreeObject.h"
#include "RegionQ.h"
#include <memory>
namespace phillib
{
namespace treelib
{
  
  class TreeObjectBase : public ITreeObject
  {
    public:
    TreeObjectBase(const std::shared_ptr<RegionQ>& region);
    virtual ~TreeObjectBase(){}
    virtual const std::shared_ptr<RegionQ>& region()const override{return _region;}
    virtual bool inside(const Index& index)const{return true;}   //toDo: dummy implementation
    private:
     const std::shared_ptr<RegionQ> _region = nullptr;
};
}
}
#endif

