#include "DialogSlopedCloud.h"

DialogSlopedCloud::DialogSlopedCloud():
  _guiUi(std::unique_ptr<Ui::DialogSlopeInput>(new Ui::DialogSlopeInput()))
{
  _guiUi->setupUi(this);
}