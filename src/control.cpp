#include "control.h"
#include "weight_note.h"

#include <QDebug>
#include <QDir>
#include <QShortcut>

Control::Control(QWidget* parent) : QWidget(parent) , m_weightHandler("./weights/")
{
    m_mainLayout = new QVBoxLayout(this);

    m_firstRow = new QHBoxLayout();
    m_manager = new VehicleManager(this);
    m_manager->loadFromFile("vehicles");
    m_firstRow->addWidget(m_manager);

    m_firstRow->addStretch();
    m_tabs = new QTabWidget;
    m_tabs->setFixedWidth(484);
    m_weightList = new WeightList;
    m_weightList->setFixedWidth(480);
    m_tabs->addTab(m_weightList, "Wiegungen");
    m_camera = new Camera("http://192.168.178.2:9000/cgi-bin/wap_capture.cgi?cam=0&");
    m_camera->setFixedWidth(480);
    m_tabs->addTab(m_camera, "Kamera");
    m_firstRow->addWidget(m_tabs);
    m_mainLayout->addLayout(m_firstRow);

    m_axisView = new AxisView();
    m_secondRow = new QHBoxLayout();
    m_secondRow->addWidget(m_axisView);
//    m_mainLayout->addLayout(m_secondRow);

    WeightNote::setRootDirectory("weight_notes/");
    this->setWindowIcon(QIcon("picture/app_icon.jpg"));

    connect(new QShortcut(QKeySequence("Ctrl+Left"), this), SIGNAL(activated()),
            this, SLOT(tabLeft()));
    connect(new QShortcut(QKeySequence("Ctrl+Right"), this), SIGNAL(activated()),
            this, SLOT(tabRight()));

#ifdef _DEBUG_
    m_waage = new Dummy();
    m_waage->show();
    connect(m_waage, SIGNAL(finish(Weight*)), this, SLOT(finishWeight(Weight*)));
    connect(m_waage, SIGNAL(nextAxis(int, Weight*)), this, SLOT(nextAxis(int, Weight*)));
#else
    m_fzw12 = new FZW12("/dev/ttyUSB0");
    connect(m_fzw12, SIGNAL(finish(Weight*)), this, SLOT(finishWeight(Weight*)));
    connect(m_fzw12, SIGNAL(nextAxis(int, Weight*)), this, SLOT(nextAxis(int, Weight*)));
#endif
}

void Control::startWeighting(Weight* weight)
{
#ifdef _DEBUG_
    m_waage->newWeight(weight);
#else
    m_fzw12->newWeight(weight);
#endif
    m_axisView->startWeighting();
    qDebug() << "starte Wiegung";
}

void Control::abortWeighting(void)
{
#ifdef _DEBUG_
    m_waage->abortWeighting();
#else
    m_fzw12->abortWeighting();
#endif
    qDebug() << "Abbruch Wiegung";
}

void Control::tabLeft(void)
{
    if (m_tabs->currentIndex() >= 1)
    {
        m_tabs->setCurrentIndex(m_tabs->currentIndex() - 1);
    }
}

void Control::tabRight(void)
{
    if (m_tabs->currentIndex() - 1 < m_tabs->count())
    {
        m_tabs->setCurrentIndex(m_tabs->currentIndex() + 1);
    }
}

void Control::nextAxis(int weightAxis, Weight* weight)
{
    qDebug() << "nextAxis(...);";

    if (weight->numberOfAxis() >= 2 || weight->numberOfAxis() == 1)
    {
        qDebug() << "YO1";

        if ((weight->axis(0) == 0) || (weight->numberOfAxis() == 1))
        {
            qDebug() << "YO2";

            if (!QDir("picture/").exists(QString(weight->vehicle()).append(".jpg")))
            {
                qDebug() << "Erstelle Fahrzeug Icon für " << weight->vehicle() << ".";

                m_camera->getPixmap().scaled(QSize(117, 75), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
                    .save(QString("./picture/").append(weight->vehicle()).append(".jpg"));
            }
        }
    }
}

void Control::finishWeight(Weight* weight)
{
    m_weightList->addWeight(weight, new WeightView(weight));
    m_manager->finishWeight();
    m_weightHandler.saveWeightToFile(weight);

    if (m_manager->weightNoteEnable())
    {
        WeightNote weightNote("vorlage_wiegeschein.tex");
        weightNote.setWeight(weight);
        weightNote.saveFile();
        weightNote.compile();
    }

    qDebug() << "Wiegung feritg";
}

Control::~Control(void)
{
#ifdef _DEBUG_
    delete m_waage;
#else
    delete m_fzw12;
#endif
}

