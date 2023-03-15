#ifndef PHILLIB_TREELIB_DATAOBJECTBASE_H_
#define PHILLIB_TREELIB_DATAOBJECTBASE_H_


#include "IDataObject.h"

class Index;

namespace phillib
{
namespace treelib
{
  class DataObjectBase : public IDataObject
  {
    public:
    DataObjectBase(const Index& index);
    virtual ~DataObjectBase(){}
    protected:
      Index _index;
};
}
}
#endif

