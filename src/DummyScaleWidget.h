#ifndef ___DUMMY_SCALE_WIDGET_H___
#define ___DUMMY_SCALE_WIDGET_H___

#include <QWidget>

#include "DummyScale.h"

namespace Ui {
class DummyScaleWidget;
}

class DummyScaleWidget : public QWidget
{
public:
    DummyScaleWidget(DummyScale& dummy, QWidget* parent = 0);

private:
    Ui::DummyScaleWidget* _ui;
    DummyScale& _dummy;
};

#endif
