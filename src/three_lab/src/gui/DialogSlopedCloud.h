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
    private:
      std::unique_ptr<Ui::DialogSlopeInput> _guiUi;
};

#endif