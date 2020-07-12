#ifndef DIALOG_RANDOM_PLANE_H_
#define DIALOG_RANDOM_PLANE_H_

#include "ui_dialog_random_plane.h"
#include <QDialog>
#include <memory>

class DialogRandomPlane : public QDialog
{
  Q_OBJECT
  public:
  DialogRandomPlane();
  virtual ~DialogRandomPlane(){}
  const int nPoints(void)const{return _guiUi->verticalSliderNpoints->value();}
  const double threshX(void)const{return _guiUi->doubleSpinBoxThreshX->value();}
  const double threshY(void)const{return _guiUi->doubleSpinBoxThreshY->value();}
  const double slopeX(void)const{return _guiUi->doubleSpinBoxSlopeX->value();}
  const double slopeY(void)const{return _guiUi->doubleSpinBoxSlopeY->value();}
  const double variance(void)const{return _guiUi->doubleSpinBoxVariance->value();}
  private:
    std::unique_ptr<Ui::DialogPlaneRandom> _guiUi;
};

#endif