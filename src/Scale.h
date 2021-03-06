#ifndef ___SCALE_H___
#define ___SCALE_H___

#include <QObject>

#include "Weighting.h"

class Vehicle;

class Scale : public QObject
{
    Q_OBJECT

public:
    Scale(void) : QObject(), _vehicle(0) { }
    virtual ~Scale(void) { }

public slots:
    virtual void start(const Vehicle* vehicle, const int good, const int suppliers, const int field);
    virtual void cancel(void);

signals:
    void finished(Weighting* weight);
    void started(void);
    void axisWeight(const int kg);
    void errorOccurred(void);

protected:
    void setNextAxisWeight(const int kg);

private:
    const Vehicle* _vehicle;
    Weighting _weighting;
};

#endif
