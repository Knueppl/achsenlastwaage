#include "Weighting.h"

#include <QDebug>

Weighting::Weighting(void)
    : _vehicle(new Vehicle),
      _weight(-1),
      _finished(false),
      _valid(false)
{

}

void Weighting::start(const Vehicle* vehicle, const int goodId, const int supplierId, const int fieldId)
{
    this->clear();

    _weight     = 0;
    _vehicle    = vehicle;
    _goodId     = goodId;
    _supplierId = supplierId;
    _fieldId    = fieldId;
}

void Weighting::clear(void)
{
    _valid = false;
    _finished = false;
    _weights.clear();
    _weight = -1;
    _vehicle = 0;
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
