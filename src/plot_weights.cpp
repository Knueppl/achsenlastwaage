#include "plot_weights.h"

#include <QStringList>
#include <QDebug>
#include <QFile>

PlotWeights::PlotWeights(const QString& directory, QWidget* parent) : QWidget(parent)
{
    m_directory = new QDir(directory);

    m_mainLayout = new QHBoxLayout(this);

    m_controlLayout = new QVBoxLayout;
    m_mainLayout->addLayout(m_controlLayout);

    m_tabs = new QTabWidget;
    m_mainLayout->addWidget(m_tabs);
}

PlotWeights::~PlotWeights(void)
{
    for (int i = 0; i < m_weights.size(); i++)
    {
        delete m_weights.at(i);
    }
}

void PlotWeights::getWeights(void)
{
    QStringList list(m_directory->entryList(QStringList() << "Wiegeschein_Nr*tex", QDir::Files, QDir::Time));

    for (int i = 0; i < list.size(); i++)
    {
        QFile file(QString(m_directory->path()).append("/").append(list.at(i)));

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Kann Datei " << file.fileName() << " nicht öffnen!";
            continue;
        }

        Weight* weight = new Weight();
        m_weights.push_front(weight);

        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (line.contains("Lieferschein Nr."))
            {
                weight->setWeightNoteNumber(line.remove("        {\\huge Lieferschein Nr. ").remove("} \\\\").toInt());
            }
            else if (line.contains("Lieferant:"))
            {
                weight->setSupplier(line.remove("            Lieferant: & ").remove("\\"));
            }
            else if (line.contains("Fahrzeug:"))
            {
                weight->setVehicle(line.remove("            Fahrzeug:  & ").remove("\\"));
            }
            else if (line.contains("Ware:"))
            {
                weight->setProduct(line.remove("            Ware:      & "));
            }
            else if (line.contains("Gesamtgewicht:}  & "))
            {
                weight->setBrutto(line.remove("            \\textbf{Gesamtgewicht:}  & ").remove(" kg\\\\").toInt());
            }
            else if (line.contains("{Tara:} & "))
            {
                weight->setTara(line.remove("            \\textbf{Tara:} & ").remove(" kg\\\\").toInt());
            }
            else if (line.contains("{Netto:} & "))
            {
                weight->setNetto(line.remove("            \\textbf{Netto:} & ").remove(" kg").toInt());
            }
            else if (line.contains("{Datum/Uhrzeit:} & "))
            {
                weight->setDate(line.remove("            \\textbf{Datum/Uhrzeit:} & ").remove("\\\\"));
            }
        }

        file.close();
    }

    this->sortWeights();
    this->saveAllToFile();
}

void PlotWeights::saveAllToFile(void)
{
    QFile file("Ausgabe.csv");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Kann Datei " << file.fileName() << " nicht öffnen!";
        return;
    }

    QTextStream out(&file);
    out << "Fahrzeug, Datum/Uhrzeit, Brutto, TARA, Netto, Lieferant, Ware\n";

    for (int i = 0; i < m_weights.size(); i++)
    {
        out << m_weights.at(i)->vehicle() << ", ";
        out << m_weights.at(i)->date()    << ", ";
        out << QString::number(m_weights.at(i)->brutto()) << ", ";
        out << QString::number(m_weights.at(i)->tara()) << ", ";
        out << QString::number(m_weights.at(i)->netto()) << ", ";
        out << m_weights.at(i)->supplier() << ", ";
        out << m_weights.at(i)->product() << "\n";
    }

    file.close();
}

void PlotWeights::sortWeights(void)
{
    for (int i = 0; i < m_weights.size(); i++)
    {
        bool found = false;

        for (int j = 0; j < m_tabs->count(); j++)
        {
            if (m_tabs->tabText(j) == m_weights.at(i)->supplier())
            {
                ((OrderedBySupplier*)m_tabs->widget(j))->addWeight(m_weights.at(i));
                found = true;
                break;
            }
        }

        if (!found)
        {
            OrderedBySupplier* obs = new OrderedBySupplier();
            obs->addWeight(m_weights.at(i));
            m_tabs->addTab(obs, m_weights.at(i)->supplier());
        }
    }
}





OrderedBySupplier::OrderedBySupplier(QWidget* parent) : QToolBox(parent)
{
    m_tree = new QTreeWidget;
    m_tree->setHeaderLabels(QStringList() << "Fahrzeug" << "Datum" << "Brutto" << "Tara" << "Netto" << "Lieferschein");
    this->addItem(m_tree, QString("Gruppiert nach Fahrzeug"));

    m_table = new QTableWidget(2, 6);
    m_table->setHorizontalHeaderLabels(QStringList() << "Fahrzeug" << "Datum" << "Brutto" << "Tara" << "Netto" << "Lieferschein");
    m_table->setSortingEnabled(true);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setItem(1, 0, new QTableWidgetItem("Summe"));
    m_table->setItem(1, 1, new QTableWidgetItem("0 kg"));
    this->addItem(m_table, QString("Tabelle"));
}

void OrderedBySupplier::addWeight(const Weight* weight)
{
    delete m_table->item(m_table->rowCount() - 1, 0);
    delete m_table->item(m_table->rowCount() - 1, 2);
    delete m_table->item(m_table->rowCount() - 1, 4);
    m_table->setRowCount(m_table->rowCount() + 1);
    m_table->setItem(m_table->rowCount() - 3, 0, new QTableWidgetItem(weight->vehicle()));
    m_table->setItem(m_table->rowCount() - 3, 1, new QTableWidgetItem(weight->date()));
    m_table->setItem(m_table->rowCount() - 3, 2, new QTableWidgetItem(QString::number(weight->brutto()).append(" kg")));
    m_table->setItem(m_table->rowCount() - 3, 3, new QTableWidgetItem(QString::number(weight->tara()).append(" kg")));
    m_table->setItem(m_table->rowCount() - 3, 4, new QTableWidgetItem(QString::number(weight->netto()).append(" kg")));
    m_table->setItem(m_table->rowCount() - 3, 5, new QTableWidgetItem(QString::number(weight->weightNoteNumber())));
    m_table->sortItems(5);
    this->calcSumTable();

    for (int i = 0; i < m_tree->topLevelItemCount(); i++)
    {
        if (m_tree->topLevelItem(i)->text(0) == weight->vehicle())
        {
            this->addChild(m_tree->topLevelItem(i), weight);
            this->calcSumTree(m_tree->topLevelItem(i));

            return;
        }
    }

    m_tree->insertTopLevelItem(0, new QTreeWidgetItem(QStringList() << weight->vehicle()));
    this->addChild(m_tree->topLevelItem(0), weight);
    this->calcSumTree(m_tree->topLevelItem(0));
}

void OrderedBySupplier::addChild(QTreeWidgetItem* top, const Weight* weight)
{
    top->addChild(new QTreeWidgetItem(QStringList() << QString("")
                                      << QString::number(weight->brutto()).append(" kg")
                                      << QString::number(weight->tara()).append(" kg")
                                      << QString::number(weight->netto()).append(" kg")
                                      << QString::number(weight->weightNoteNumber())));
}

void OrderedBySupplier::calcSumTable(void)
{
    m_table->setItem(m_table->rowCount() - 1, 0, new QTableWidgetItem("Summe"));

    int brutto = 0;
    int netto = 0;

    for (int i = 0; i < m_table->rowCount() - 2; i++)
    {
        brutto += m_table->item(i, 2)->text().remove(" kg").toInt();
        netto  += m_table->item(i, 4)->text().remove(" kg").toInt();
    }

    m_table->setItem(m_table->rowCount() - 1, 2, new QTableWidgetItem(QString::number(brutto).append(" kg")));
    m_table->setItem(m_table->rowCount() - 1, 4, new QTableWidgetItem(QString::number(netto).append(" kg")));
}

void OrderedBySupplier::calcSumTree(QTreeWidgetItem* top)
{
    int brutto = 0;
    int netto = 0;

    for (int i = 0; i < top->childCount(); i++)
    {
        brutto += top->child(i)->text(2).remove(" kg").toInt();
        netto  += top->child(i)->text(4).remove(" kg").toInt();
    }

    top->setText(2, QString::number(brutto).append(" kg"));
    top->setText(4, QString::number(netto).append(" kg"));
}
