#include <QFile>
#include <QDebug>
#include <QDir>

#include "weight_list.h"

/*********************************************************************/
/* Class WeightView                                                  */
/*********************************************************************/

WeightView::WeightView(const Weight* weight, QWidget* parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_firstRow = new QHBoxLayout;
    m_vehicle = new QLabel(weight->vehicle(), this);
    m_vehicle->setFont(QFont("Arial", 16, QFont::Bold));
    m_firstRow->addWidget(m_vehicle);

    m_axisLayout = new QHBoxLayout;
    m_axisState = new QLabel*[weight->numberOfAxis()];
    for (int i = 0; i < weight->numberOfAxis(); i++)
    {
        m_axisState[i] = new QLabel(this);
        if (weight->axisState(i))
        {
            m_axisState[i]->setPixmap(QPixmap("./picture/achse_gut.png"));
        }
        else
        {
            m_axisState[i]->setPixmap(QPixmap("./picture/achse_schlecht.png"));
        }
        m_axisLayout->addWidget(m_axisState[i]);
    }
    m_axisLayout->addStretch();
    m_firstRow->addLayout(m_axisLayout);
    m_layout->addLayout(m_firstRow);

    QString tmp("Brutto: ");
    tmp.append(QString::number(weight->brutto()));
    m_brutto = new QLabel(tmp, this);
    m_brutto->setFont(QFont("Arial", 10, QFont::Bold));
    m_secondRow = new QGridLayout;
    m_secondRow->addWidget(m_brutto, 0, 0);

    tmp.clear();
    tmp.append("Tara: ");
    tmp.append(QString::number(weight->tara()));
    m_tara = new QLabel(tmp, this);
    m_tara->setFont(QFont("Arial", 10, QFont::Bold));
    m_secondRow->addWidget(m_tara, 0, 1);

    tmp.clear();
    tmp.append("Netto: ");
    tmp.append(QString::number(weight->netto()));
    m_netto = new QLabel(tmp, this);
    m_netto->setFont(QFont("Arial", 10, QFont::Bold));
    m_secondRow->addWidget(m_netto, 0, 2);

    m_date = new QLabel(QString("Datum: ").append(weight->dateTime().date().toString()), this);
    m_date->setFont(QFont("Arial", 10));
    m_secondRow->addWidget(m_date, 1, 0);

    m_time = new QLabel(QString("Uhrzeit: ").append(weight->dateTime().time().toString()), this);
    m_time->setFont(QFont("Arial", 10));
    m_secondRow->addWidget(m_time, 1, 1);
    m_layout->addLayout(m_secondRow);
}

WeightView::~WeightView(void)
{
    delete m_axisState;
}

/*********************************************************************/
/* Class WeightList                                                  */
/*********************************************************************/

WeightList::WeightList(QWidget* parent) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    this->setLayout(m_mainLayout);
    m_listWidget = new QListWidget(this);
    m_listWidget->setIconSize(QSize(113, 75));
    m_mainLayout->addWidget(m_listWidget);
}

WeightList::~WeightList(void)
{

}

void WeightList::addWeight(Weight* weight, QWidget* view)
{
    m_listWidget->insertItem(0, weight);
    m_listWidget->setItemWidget(weight, view);
}

/*********************************************************************/
/* Class Weight                                                      */
/*********************************************************************/

Weight::Weight(const QString& vehicle, const int tara, const int numberOfAxis,
               const QString& product, const QString& supplier, QListWidget* parent, int type) : QListWidgetItem(parent, type)
{
    m_weightNoteNumber = 0;
    m_brutto = 0;
    m_tara = tara;
    m_netto = m_brutto - m_tara;
    m_vehicle = vehicle;
    m_product = product;
    m_supplier = supplier;

    if (QDir("./picture/").exists(QString(m_vehicle).append(".jpg")))
    {
        this->setIcon(QIcon(QString("./picture/").append(m_vehicle).append(".jpg")));
    }
    else
    {
        this->setIcon(QIcon("./picture/icon_weight.jpg"));
    }

    this->setSizeHint(QSize(300, 80));
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, 80));
    linearGrad.setColorAt(0, Qt::gray);
    linearGrad.setColorAt(1, Qt::white);
    this->setBackground(QBrush(linearGrad));

    m_numberOfAxis = numberOfAxis;
    m_axisState = new bool[m_numberOfAxis];
    m_axis = new int[m_numberOfAxis];
    for (int i = 0; i < m_numberOfAxis; i++)
    {
        m_axisState[i] = true;
        m_axis[i] = 0;
    }

    m_dateTime = QDateTime::currentDateTime();
}

Weight::~Weight(void)
{
    delete [] m_axisState;
    delete [] m_axis;
}

int Weight::addAxis(const int weight, const bool state) // returns the current axis
{
    if (weight > 0)
    {
        for (int i = 0; i < m_numberOfAxis; i++)
        {
            if (!m_axis[i])
            {
                m_axis[i] = weight;
                m_axisState[i] = state;
                m_brutto += weight;
                m_netto = m_brutto - m_tara;

                qDebug() << "Achse " << i + 1 << ": " << weight << "kg";
                qDebug() << "State: " << state;

                return ++i;
            }
        }
    }

    return 0;
}

/*********************************************************************/
/* Class WeightHandler                                               */
/*********************************************************************/
WeightHandler::WeightHandler(const QString& workingDirectory)
{
    m_workingDirectory = workingDirectory;
}

void WeightHandler::saveWeightToFile(const Weight* weight) const
{
    QString fileName(m_workingDirectory);
    (fileName += weight->vehicle()) += '_';
    fileName += weight->dateTime().toString(Qt::ISODate);
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "Fahrzeug : " << weight->vehicle() << '\n';
        out << "Datum    : " << weight->dateTime().date().toString(Qt::ISODate) << '\n';
        out << "Uhrzeit  : " << weight->dateTime().time().toString(Qt::ISODate) << '\n';
        out << "Brutto   : " << weight->brutto() << '\n';
        out << "TARA     : " << weight->tara() << '\n';
        out << "Netto    : " << weight->netto() << '\n';
        out << "Ware     : " << weight->product() << '\n';
        out << "Lieferant: " << weight->supplier() << '\n';

        for (int i = 0; i < weight->numberOfAxis(); i++)
        {
            out << "Achse " << i + 1 << " : " << weight->axis(i) << '\n';
        }

        file.close();
    }
}

Weight* WeightHandler::loadWeightFromFile(void) const
{
    return new Weight;
}
