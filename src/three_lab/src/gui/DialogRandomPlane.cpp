#include "DialogRandomPlane.h"

DialogRandomPlane::DialogRandomPlane():
  _guiUi(std::unique_ptr<Ui::DialogPlaneRandom>(new Ui::DialogPlaneRandom()))
{
  _guiUi->setupUi(this);
}