#include "CppHelper.h"
#include <sstream>

namespace phillib
{
  namespace cpp_helper
  {

  CppHelper::CppHelper()
  {
      _gui.show();
  }
  void CppHelper::writeFile(void)
  {
    QVector<QString> nameSpaces;
    _gui.nameSpaces(nameSpaces);

    QVector<QString> baseClasses;
    _gui.baseClasses(baseClasses);

    QVector<QString> headerFiles;
    _gui.headerFiles(headerFiles);

    std::stringstream ss;
    std::string stringNameSpaces;
    for(auto& iter : nameSpaces)
    {
      stringNameSpaces += iter.toStdString();
      stringNameSpaces += '_';
    }
  }
  }
}