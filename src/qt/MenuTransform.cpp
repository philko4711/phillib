#include "MenuTransform.h"

namespace phillib {
namespace qt {
MenuTransform::MenuTransform(QWidget *parent)
    : QWidget(parent), _guiUi(std::make_unique<Ui::WidgetTransform>()),_T(Eigen::Affine3f::Identity()) {
      _guiUi->setupUi(this);
  connect(_guiUi->doubleSpinBoxTx, SIGNAL(valueChanged(double)), this, SLOT(parameterChanged(double)));
  connect(_guiUi->doubleSpinBoxTy, SIGNAL(valueChanged(double)), this, SLOT(parameterChanged(double)));
  connect(_guiUi->doubleSpinBoxTz, SIGNAL(valueChanged(double)), this, SLOT(parameterChanged(double)));
  connect(_guiUi->doubleSpinBoxRr, SIGNAL(valueChanged(double)), this, SLOT(parameterChanged(double)));
  connect(_guiUi->doubleSpinBoxRp, SIGNAL(valueChanged(double)), this, SLOT(parameterChanged(double)));
  connect(_guiUi->doubleSpinBoxRy, SIGNAL(valueChanged(double)), this, SLOT(parameterChanged(double)));
  this->show();
    }
void MenuTransform::parameterChanged(const double dummy) {
  _T.translation() << _guiUi->doubleSpinBoxTx->value(), _guiUi->doubleSpinBoxTy->value(), _guiUi->doubleSpinBoxTz->value();
  _T.rotate(Eigen::AngleAxisf(_guiUi->doubleSpinBoxRr->value(), Eigen::Vector3f::UnitX()) *
            Eigen::AngleAxisf(_guiUi->doubleSpinBoxRp->value(), Eigen::Vector3f::UnitY()) *
            Eigen::AngleAxisf(_guiUi->doubleSpinBoxRy->value(), Eigen::Vector3f::UnitZ()));
  emit this->transformChanged();
}
} // namespace qt
} // namespace phillib
