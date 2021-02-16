#ifndef PHILLIB_UTILS_CPP_HELPER_CPP_HELPER_H_
#define PHILLIB_UTILS_CPP_HELPER_CPP_HELPER_H_

#include <QtCore/QObject>
#include "gui/MainWindow.h"

namespace phillib
{
  namespace cpp_helper
  {
    class CppHelper : public QObject
    {
      Q_OBJECT
      public:
      CppHelper();
      virtual ~CppHelper(){}
      public slots:
        void writeFile();
      private:
        MainWindow _gui;

    };
  }
}

#endif