#ifndef PHILLIB_CPP_HELPER_MAIN_WINDOW_H_
#define PHILLIB_CPP_HELPER_MAIN_WINDOW_H_

#include <QtWidgets/QMainWindow>
#include <memory>
#include "ui_main_window.h"
#include <QtCore/QVector>
#include <QtCore/QString>
namespace phillib
{
  namespace cpp_helper
  {
    class CppHelper;
    class MainWindow : public QMainWindow
    {
      public: 
        MainWindow(CppHelper& parent);
        virtual ~MainWindow(){}
        unsigned int nameSpaces(QVector<QString>& nameSpaces)const;
        unsigned int baseClasses(QVector<QString>& baseClasses)const;
        unsigned int headerFiles(QVector<QString>& headerFiles)const;
        bool generateCpp(void)const{return _guiUi->checkBox->isChecked();}
        QString className()const;
                private:
          std::unique_ptr<Ui::MainWindow> _guiUi;
          CppHelper& _parent;
    };
  }
}

#endif