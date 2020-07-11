#ifndef DIALOG_SLOPED_CLOUD_H_
#define DIALOG_SLOPED_CLOUD_H_

#include <QDialog>
#include <memory>
#include "ui_dialog_sloped_cloud.h"

class DialogSlopedCloud : public QDialog
{
  Q_OBJECT
  public:
    DialogSlopedCloud();
    virtual ~DialogSlopedCloud(){}
    const double threshXdim()const{return _guiUi->doubleSpinBoxThreshX->value();}
    const double threshYdim()const{return _guiUi->doubleSpinBoxThreshY->value();}
    const double slopeX()const{return _guiUi->doubleSpinBoxSlopeX->value();}
    const double slopeY()const{return _guiUi->doubleSpinBoxSlopeY->value();}
    const double zVariance(void)const{return _guiUi->doubleSpinBoxZvariance->value();}
    const double resolution(void)const{return _guiUi->doubleSpinBoxResolution->value();}
    private:
      std::unique_ptr<Ui::DialogSlopeInput> _guiUi;
};

#endif