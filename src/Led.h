#ifndef ___LED_H___
#define ___LED_H___

#include <QWidget>

class LED : public QWidget
{
public:
    LED(const QColor& color, QWidget* parent = 0);

    void setState(const bool state)
    {
        m_state = state;
        this->update();
    }

    bool state(void) const { return m_state; }

protected:
    void paintEvent(QPaintEvent*);

private:
    bool   m_state;
    QColor m_color;
};

#endif
