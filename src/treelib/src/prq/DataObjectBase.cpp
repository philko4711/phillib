#include "DataObjectBase.h"
#include "Index.h"

namespace phillib
{

  namespace treelib
  {

    DataObjectBase::DataObjectBase(const Index& index):_index(index) {}
    bool DataObjectBase::inside(const Index& index)const
    {

    }
  }
}