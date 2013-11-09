#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <QWebView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QCheckBox>
#include <QSpinBox>

class Camera : public QWidget
{
    Q_OBJECT;

public:
    Camera(const char* url, QWidget* parent = 0);

    QPixmap getPixmap(void) { return QPixmap::grabWidget(this, 12, 12, this->width() - 8, this->width() * 0.8 - 12); }

private slots:
    void toggleTimer(bool);

private:
    QWebView*    m_webView;
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_optionsLayout;
    QPushButton* m_buttonRefresh;
    QCheckBox*   m_timerEnable;
    QSpinBox*    m_timerValue;
    QTimer*      m_timer;
};

class Test : public QObject
{
    Q_OBJECT;

public:
    Test(Camera* camera)
    {
        m_camera = camera;
    }

public slots:
    void test(void)
    {
        m_camera->getPixmap().scaled(QSize(117, 75), Qt::IgnoreAspectRatio, Qt::SmoothTransformation).save("test.jpg");
    }

private:
    Camera* m_camera;
};

#endif
