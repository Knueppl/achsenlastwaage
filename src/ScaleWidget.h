#ifndef ___SCALE_WIDGET_H___
#define ___SCALE_WIDGET_H___

#include <QWidget>

class QGraphicsView;
class WeightingScene;

class ScaleWidget : public QWidget
{
    Q_OBJECT

public:
    ScaleWidget(QWidget* parent = 0);

public slots:
    void start(void);

private:
    WeightingScene* _scene;
    QGraphicsView* _view;
};

#endif
