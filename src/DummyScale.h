#ifndef ___DUMMY_SCALE_H___
#define ___DUMMY_SCALE_H___

#include "Scale.h"

class DummyScale : public Scale
{
    Q_OBJECT

public:
    DummyScale(void);
    virtual ~DummyScale(void);

public slots:
    void receiveAxisWeight(const int kg);
};

#endif
