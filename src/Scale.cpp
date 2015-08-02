#include "Scale.h"

#include <QDebug>

void Scale::start(const Vehicle* vehicle)
{
    qDebug() << "scale: start weighting.";
    _weighting.start(vehicle);
    emit this->started();
}

void Scale::cancel(void)
{
    qDebug() << "scale: cancel the current weighting.";
    _weighting.clear();
    emit this->finished(0);
}

void Scale::setNextAxisWeight(const int kg)
{
    _weighting << kg;
    emit this->axisWeight(kg);
    qDebug() << "scale: next axis weight set to " << kg << ".";

    if (_weighting.finished())
    {
        qDebug() << "scale: weighting finished.";
        emit this->finished(new Weighting(_weighting));
    }
}
