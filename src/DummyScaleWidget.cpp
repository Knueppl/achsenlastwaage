#include "DummyScaleWidget.h"
#include "ui_DummyScaleWidget.h"

#include <QDebug>

DummyScaleWidget::DummyScaleWidget(Scale* dummy, QWidget* parent)
    : QWidget(parent),
      _ui(new Ui::DummyScaleWidget)
{
    _ui->setupUi(this);
    _ui->_pushSend->setDisabled(true);
    _ui->_pushAbbort->setDisabled(true);
    _ui->_spinWeight->setDisabled(true);

    _scale = dynamic_cast<DummyScale*>(dummy);

    if (!_scale)
    {
        qDebug() << "DummyScaleWidget: dummy is not from type DummyScale.";
        return;
    }

    this->connect(_ui->_pushAbbort, SIGNAL(clicked()), dummy, SLOT(cancel()));
    this->connect(_ui->_pushClose, SIGNAL(clicked()), this, SLOT(close()));
    this->connect(_ui->_pushSend, SIGNAL(clicked()), this, SLOT(sendWeight()));
    this->connect(dummy, SIGNAL(started()), this, SLOT(start()));
    this->connect(dummy, SIGNAL(finished(Weighting*)), this, SLOT(finish(Weighting*)));
}

void DummyScaleWidget::start(void)
{
    _ui->_pushSend->setEnabled(true);
    _ui->_pushAbbort->setEnabled(true);
    _ui->_spinWeight->setEnabled(true);
}

void DummyScaleWidget::finish(Weighting*)
{
    _ui->_pushSend->setDisabled(true);
    _ui->_pushAbbort->setDisabled(true);
    _ui->_spinWeight->setDisabled(true);
}

void DummyScaleWidget::sendWeight(void)
{
    _scale->receiveAxisWeight(_ui->_spinWeight->value());
}
