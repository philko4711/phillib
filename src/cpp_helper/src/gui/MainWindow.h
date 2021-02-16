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
    class MainWindow : public QMainWindow
    {
      public: 
        MainWindow();
        virtual ~MainWindow(){}
        unsigned int nameSpaces(QVector<QString>& nameSpaces)const;
        unsigned int baseClasses(QVector<QString>& baseClasses)const;
        unsigned int headerFiles(QVector<QString>& headerFiles)const;
        QString className()const;
                private:
          std::unique_ptr<Ui::MainWindow> _guiUi;
    };
  }
}

#endif