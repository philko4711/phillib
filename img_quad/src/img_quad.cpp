#include <QtWidgets/QApplication>
#include <treelib/prq/TreePrq.h>

int main(int argc, char** argv) 
{ 
    QApplication app(argc, argv);
    phillib::treelib::TreePrq tree(2048, 0.1f);
    return app.exec(); 
    }