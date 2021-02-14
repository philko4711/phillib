#ifndef PHILLIB_CPP_HELPER_MAIN_WINDOW_H_
#define PHILLIB_CPP_HELPER_MAIN_WINDOW_H_

#include <QtWidgets/QMainWindow>
#include <memory>
#include "ui_main_window.h"
namespace phillib
{
  namespace cpp_helper
  {
    class MainWindow : public QMainWindow
    {
      public: 
        MainWindow();
        virtual ~MainWindow(){}
        private:
          std::unique_ptr<Ui::MainWindow> _guiUi;
    };
  }
}

#endif