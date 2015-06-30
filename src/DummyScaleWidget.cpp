#include "DummyScaleWidget.h"
#include "ui_DummyScaleWidget.h"

DummyScaleWidget::DummyScaleWidget(DummyScale& dummy, QWidget* parent)
    : QWidget(parent),
      _dummy(dummy),
      _ui(new Ui::DummyScaleWidget)
{
    _ui->setupUi(this);
}
