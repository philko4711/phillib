#ifndef PHILLIB_TREELIB_TREEPRQ_H_
#define PHILLIB_TREELIB_TREEPRQ_H_

#include <memory>
#include <vector>
#include "IDataObject.h"

namespace phillib
{
namespace treelib
{
  class ITreeObject;
  class TreePrq
  {
    public:
    TreePrq(const float lengthEdge, const float resolutionCell);
    virtual ~TreePrq(){}
    void push(std::vector<std::shared_ptr<IDataObject> >& dataNew);
    const bool empty(void)const;
    void print();
    private:
      std::shared_ptr<ITreeObject> _tree;
      const float _res;
};
}
}
#endif

