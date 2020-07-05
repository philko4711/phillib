#include "MainWindowLab.h"
#include "DialogSlopedCloud.h"
#include <memory>
#include <QDebug>
MainWindowLab::MainWindowLab():
_guiUi(std::unique_ptr<Ui::MainWindowThLab>(new Ui::MainWindowThLab()))
{
  _guiUi->setupUi(this);
  connect(_guiUi->actionCreateRandomPlane, SIGNAL(triggered()), this, SLOT(slopedInput()));
}

void MainWindowLab::slopedInput()
{
   static DialogSlopedCloud dialog; 
   int retval = dialog.exec();
   if(retval == QDialog::DialogCode::Accepted)
   {
     qDebug() << __PRETTY_FUNCTION__ << " hudeldudel";
   }
   else
   {
     return;
   }
   
}