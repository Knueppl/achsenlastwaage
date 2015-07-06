#ifndef ___WEIGHTING_H___
#define ___WEIGHTING_H___

#include <QVector>

class Vehicle;

class Weighting
{
public:
    Weighting(void);

    int weight(void) const { return _weight; }
    int axes(void) const { return _weights.size(); }
    const QVector<int> weights(void) const { return _weights; }
    const Vehicle* vehicle(void) const { return _vehicle; }

    void start(const Vehicle* vehicle);
    void clear(void);
    bool finished(void) const { return _finished; }
    bool valid(void) const;

    Weighting& operator<<(const int kg);

private:
    const Vehicle* _vehicle;
    QVector<int> _weights;
    int _weight;
    bool _finished;
};

#endif
