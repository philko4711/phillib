#include "MainWindow.h"
#include "CppHelper.h"
namespace phillib
{
namespace cpp_helper
{
MainWindow::MainWindow(CppHelper& parent)
    : _guiUi(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow()))
    , _parent(parent)
{
  _guiUi->setupUi(this);
  connect(_guiUi->pushButton, SIGNAL(clicked()), &_parent, SLOT(writeFile()));
}
unsigned int MainWindow::nameSpaces(QVector<QString>& nameSpaces) const
{
  for(unsigned int i = 0; i < _guiUi->comboBoxNamespaces->count(); i++)
    nameSpaces.push_back(_guiUi->comboBoxNamespaces->itemText(i));
  return nameSpaces.size();
}

unsigned int MainWindow::baseClasses(QVector<QString>& baseClasses) const
{
  for(unsigned int i = 0; i < _guiUi->comboBoxNamespaces->count(); i++)
    baseClasses.push_back(_guiUi->comboBoxNamespaces->itemText(i));
  return baseClasses.size();
}

unsigned int MainWindow::headerFiles(QVector<QString>& headerFiles) const
{
  for(unsigned int i = 0; i < _guiUi->comboBoxHeaderFiles->count(); i++)
    headerFiles.push_back(_guiUi->comboBoxHeaderFiles->itemText(i));
  return headerFiles.size();
}

QString MainWindow::className() const { return _guiUi->lineEdit->text(); }

} // namespace cpp_helper
} // namespace phillib