#include "MainWindow.h"

namespace phillib {
namespace cpp_helper {
MainWindow::MainWindow()
    : _guiUi(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow())) {
  _guiUi->setupUi(this);
}
} // namespace cpp_helper
} // namespace phillib