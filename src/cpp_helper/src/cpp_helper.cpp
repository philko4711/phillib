#include "CppHelper.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  phillib::cpp_helper::CppHelper cppHelper;
  return app.exec();
}
