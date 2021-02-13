#ifndef PHILLIB_UTILS_CPP_HELPER_CPP_HELPER_H_
#define PHILLIB_UTILS_CPP_HELPER_CPP_HELPER_H_

#include <QtCore/QObject>

namespace phillib
{
  namespace cpp_helper
  {
    class CPPHelper : public QObject
    {
      public:
      CPPHelper();
      virtual ~CPPHelper(){}

    };
  }
}

#endif