#ifndef ___WEIGHTING_SCENE_H___
#define ___WEIGHTING_SCENE_H___

#include <QGraphicsScene>
#include <QTimer>

#include "VehicleButton.h"

class Vehicle;

class WeightingScene : public QGraphicsScene
{
    Q_OBJECT

public:
    WeightingScene(QObject* parent = 0);
    virtual ~WeightingScene(void);

    void start(const Vehicle* vehicle);
    void setNextWeight(const int kg);

public slots:
    void showError(void);

private slots:
    void tick(void);

private:
    QGraphicsPixmapItem* _vehicleItem;
    QGraphicsTextItem* _axisWeightItem;
    QGraphicsSimpleTextItem* _vehicleNameItem;
    QGraphicsTextItem* _axesWeightsItem;
    QGraphicsTextItem* _axesLabelItem;
    QGraphicsTextItem* _weightsItem;
    QGraphicsTextItem* _weightsLabelItem;
    const Vehicle* _vehicle;
    VehicleButton::VehicleType _vehicleType;
    int _currentAxis;
    int _sum;
    bool _showError;

    QTimer _timer;
};

#endif
