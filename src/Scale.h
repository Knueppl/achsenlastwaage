#ifndef ___SCALE_H___
#define ___SCALE_H___

#include <QObject>

class Vehicle;
class Weight;

class Scale : public QObject
{
    Q_OBJECT

public:
    Scale(void) : QObject() { }
    virtual ~Scale(void) { }

public slots:
    virtual void start(const Vehicle* vehicle) = 0;
    virtual void cancel(void) = 0;

signals:
    virtual void finished(Weight* weight) = 0;
};

#endif
