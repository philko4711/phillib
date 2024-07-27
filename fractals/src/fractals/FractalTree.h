#ifndef PHILLIB_FRACTALTREE_H_
#define PHILLIB_FRACTALTREE_H_

#include <QtCore/QLineF>
#include <vector>
#include <memory>

namespace phillib
{
  class FractalTree
  {
    public:
    FractalTree(const QLineF& lineInitial);
    virtual ~FractalTree(){}
    void iterate();
    private:
    std::vector<QLineF> _lines;
};
}
#endif

