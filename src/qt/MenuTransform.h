#ifndef PHILLIB_QT_MENUTRANSFORM_H_
#define PHILLIB_QT_MENUTRANSFORM_H_


#include <QtWidgets/QWidget>
#include "ui_menuTransform.h"
#include <memory>
#include <Eigen/Dense>

namespace phillib
{
namespace qt
{
  class MenuTransform : public QWidget
  {
    Q_OBJECT
    public:
    MenuTransform(QWidget* parent = nullptr);
    virtual ~MenuTransform(){}
    const Eigen::Affine3f& T(void)const{return _T;}
    public slots:
      void parameterChanged(const double dummy);
    signals:
      void transformChanged();  
    private:
      std::unique_ptr<Ui::WidgetTransform> _guiUi;
      Eigen::Affine3f _T;
};
}
}
#endif

