#ifndef ___WEIGHTING_H___
#define ___WEIGHTING_H___

#include <QVector>

#include "Vehicle.h"

class Weighting
{
public:
    Weighting(void);

    int weight(void) const { return _weight; }
    int axes(void) const { return _weights.size(); }
    const QVector<int> weights(void) const { return _weights; }
    const Vehicle* vehicle(void) const { return _vehicle; }

    void start(const Vehicle* vehicle, const int goodId = 0, const int supplierId = 0, const int fieldId = 0);
    void clear(void);
    bool finished(void) const { return _finished; }
    bool valid(void) const { return _valid; }
    bool setValid(const bool valid) { _valid = valid; }

    int brutto(void) const { return _weight; }
    int tara(void) const { return _vehicle->tara(); }
    int netto(void) const { return this->brutto() - this->tara(); }

    int goodId(void) const { return _goodId; }
    int supplierId(void) const { return _supplierId; }
    int fieldId(void) const { return _fieldId; }

    Weighting& operator<<(const int kg);

private:
    const Vehicle* _vehicle;
    int _goodId;
    int _supplierId;
    int _fieldId;
    QVector<int> _weights;
    int _weight;
    bool _finished;
    bool _valid;
};

#endif
