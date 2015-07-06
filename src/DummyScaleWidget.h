#ifndef ___DUMMY_SCALE_WIDGET_H___
#define ___DUMMY_SCALE_WIDGET_H___

#include <QWidget>

#include "DummyScale.h"

class Weighting;

namespace Ui {
class DummyScaleWidget;
}

class DummyScaleWidget : public QWidget
{
    Q_OBJECT

public:
    DummyScaleWidget(Scale* dummy, QWidget* parent = 0);

private slots:
    void start(void);
    void finish(Weighting*);
    void sendWeight(void);

private:
    Ui::DummyScaleWidget* _ui;
    DummyScale* _scale;
};

#endif
