#ifndef ___WEIGHTING_SCENE_H___
#define ___WEIGHTING_SCENE_H___

#include <QGraphicsScene>
#include <QTimer>

#include "VehicleButton.h"

class WeightingScene : public QGraphicsScene
{
    Q_OBJECT

public:
    WeightingScene(QObject* parent = 0);
    virtual ~WeightingScene(void);

    void start(const int axes);
    void setNextWeight(const int kg);

private slots:
    void tick(void);

private:
    QGraphicsPixmapItem* _vehicle;
    VehicleButton::VehicleType _vehicleType;
    int _currentAxis;
    QTimer _timer;
};

#endif
