#include <QtWidgets/QApplication>
#include <treelib/prq/TreePrq.h>
#include "gui/MainWindow.h"

int main(int argc, char** argv) 
{ 
    QApplication app(argc, argv);
    phillib::treelib::TreePrq tree(2048, 0.1f);
    phillib::img_quad::MainWindow _gui;
    _gui.show();
    return app.exec(); 
    }