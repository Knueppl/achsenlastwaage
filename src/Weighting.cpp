#include "Weighting.h"
#include "Vehicle.h"

#include <QDebug>

Weighting::Weighting(void)
    : _vehicle(0),
      _weight(-1),
      _finished(false)
{

}

void Weighting::start(const Vehicle* vehicle)
{
    this->clear();
    _weight = 0;
    _vehicle = vehicle;
}

void Weighting::clear(void)
{
    _finished = false;
    _weights.clear();
    _weight = -1;
    _vehicle = 0;
}

bool Weighting::valid(void) const
{
    return _finished && _weight.size() >= _vehicle->axes();
}

Weighting& Weighting::operator<<(const int kg)
{
    if (_finished)
    {
        qDebug() << "weighting: weighting is complete. No more input will accepted.";
        return *this;
    }

    _weights.push_back(kg);
    _weight += kg;

    if (_weights.size() >= _vehicle->axes())
    {
        qDebug() << "weighting: finished.";
        _finished = true;
    }

    return *this;
}
