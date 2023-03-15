#include "TreePrq.h"
#include "DataObjectPoint.h"
#include "IDataObject.h"
#include "RegionQ.h"
#include "Point.h"
#include <memory>
#include <vector>

int main(int argc, const char** argv) 
{
    std::vector<std::shared_ptr<phillib::treelib::IDataObject> > data;
    data.push_back(std::make_shared<phillib::treelib::DataObjectPoint>(phillib::treelib::Point(1.0f, 1.0f)));
    data.push_back(std::make_shared<phillib::treelib::DataObjectPoint>(phillib::treelib::Point(0.5f, 1.0f)));
    data.push_back(std::make_shared<phillib::treelib::DataObjectPoint>(phillib::treelib::Point(1.0f, 1.0f)));

    phillib::treelib::TreePrq tree(2048, 0.10f);
    tree.print();
    tree.push(data);
    tree.print();
    return 0;
}