#include "camera.h"

Camera::Camera(const char* url, QWidget* parent) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    m_webView = new QWebView;
    m_webView->load(QUrl(url));
    m_mainLayout->addWidget(m_webView);

    m_optionsLayout = new QHBoxLayout;
    m_buttonRefresh = new QPushButton("Neu laden");
    m_optionsLayout->addWidget(m_buttonRefresh);
    m_timerEnable = new QCheckBox("timer");
    m_optionsLayout->addWidget(m_timerEnable);
    m_timerValue = new QSpinBox;
    m_timerValue->setMaximum(5000);
    m_timerValue->setMinimum(100);
    m_optionsLayout->addWidget(m_timerValue);
    m_mainLayout->addLayout(m_optionsLayout);

    m_timer = new QTimer(this);

    connect(m_buttonRefresh, SIGNAL(clicked()), m_webView, SLOT(reload()));
    connect(m_timerEnable, SIGNAL(toggled(bool)), this, SLOT(toggleTimer(bool)));
    connect(m_timer, SIGNAL(timeout()), m_webView, SLOT(reload()));
}

void Camera::toggleTimer(bool state)
{
    if (state)
    {
        m_timer->start(m_timerValue->value());
    }
    else
    {
        m_timer->stop();
    }
}
