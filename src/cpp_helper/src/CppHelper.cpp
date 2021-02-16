#include "CppHelper.h"
#include <sstream>
#include <iostream>
#include <QtCore/QtDebug>

namespace phillib
{
  namespace cpp_helper
  {

  CppHelper::CppHelper():_gui(*this)
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
    QString className = _gui.className();
    QStringList strList = className.split(".");
    for(auto& iter : strList)
      qDebug() << __PRETTY_FUNCTION__ << iter << " ";  
    stringNameSpaces += strList.begin()->toStdString(); 
    stringNameSpaces += "_";

    qDebug() << __PRETTY_FUNCTION__ << " namespaces: " << QString(stringNameSpaces.c_str()).toUpper();

    ss << "#ifndef " << QString(stringNameSpaces.c_str()).toUpper().toStdString() << std::endl;
    ss << "#define" << QString(stringNameSpaces.c_str()).toUpper().toStdString() << std::endl;
    ss << std::endl << std::endl;
    ss << "  class " << className.toStdString() << "\n  {\n    " << className.toStdString() << "();" << "\n    virtual~" << className.toStdString() << "();\n";
    ss << "#endif";
    qDebug() << __PRETTY_FUNCTION__ << "\n" <<ss.str().c_str();
  }
  }
}