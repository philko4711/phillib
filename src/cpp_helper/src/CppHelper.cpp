#include "CppHelper.h"
#include <sstream>
#include <iostream>
#include <QtCore/QtDebug>
#include <QtCore/QFile>
#include <QtWidgets/QFileDialog>

namespace phillib
{
  namespace cpp_helper
  {

  CppHelper::CppHelper():_gui(*this)
  {
      _gui.show();

  }
  void CppHelper::writeFile()
  {
    const QString path = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());    

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
    //QStringList strList = className.split(".");
    // for(auto& iter : strList)
    //   qDebug() << __PRETTY_FUNCTION__ << iter << " ";  
    stringNameSpaces += className.toStdString();//strList.begin()->toStdString(); 
    stringNameSpaces += "_H_";

    qDebug() << __PRETTY_FUNCTION__ << " namespaces:" << QString(stringNameSpaces.c_str()).toUpper();

    ss << "#ifndef " << QString(stringNameSpaces.c_str()).toUpper().toStdString() << std::endl;
    ss << "#define " << QString(stringNameSpaces.c_str()).toUpper().toStdString() << std::endl;
    ss << std::endl << std::endl;
    for(auto& iter : nameSpaces)
      ss << iter.toStdString() <<"\n{\n";

  
    ss << "  class " << className.toStdString();
    if(baseClasses.size())
    {
      ss << " : public ";
      for(int i = 0; i < baseClasses.size() - 1; i++)                          //auto& iter : baseClasses)
        ss << baseClasses[i].toStdString() << ", ";
      ss << baseClasses.last().toStdString();  
      //ss << "\n";
    }
    //for(auto& iter : )
    ss << "\n  {\n    " << className.toStdString() << "();" << "\n    virtual ~" << className.toStdString() << "();\n};\n";

    for(int i = 0; i < nameSpaces.size(); i++)
      ss << "}\n";
    ss << "#endif\n\n";
    qDebug() << __PRETTY_FUNCTION__ << "\n" <<ss.str().c_str();
    QFile fileHeader(path + QString("/") + className + QString(".h"));
    if (!fileHeader.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream outHeader(&fileHeader);
    outHeader << QString(ss.str().c_str());
    fileHeader.close();

    if(!_gui.generateCpp())
      return;

    ss.str("");
    ss << "#include \"" << className.toStdString() << ".h\"";
    ss << "\n\n\n";
    ss << className.toStdString() << "::" << className.toStdString() << "()\n{\n}\n";

    QFile fileCpp(path + QString("/") + className + QString(".cpp"));
    if (!fileCpp.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

         QTextStream outCpp(&fileCpp);
    outCpp << QString(ss.str().c_str());
    fileCpp.close();
  }
  }
}