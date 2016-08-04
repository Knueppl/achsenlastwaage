#include "WeightingView.h"
#include "ui_WeightingView.h"

#include <QDebug>

WeightingView::WeightingView(QWidget* parent)
    : QWidget(parent),
      _ui(new Ui::WeightingView),
      _database(0)
{
    _ui->setupUi(this);
    _ui->_table->setColumnCount(9);
    _ui->_table->setHorizontalHeaderItem(0, new QTableWidgetItem("Wiegung"));
    _ui->_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Fahrzeug"));
    _ui->_table->setHorizontalHeaderItem(2, new QTableWidgetItem("Datum/Uhrzeit"));
    _ui->_table->setHorizontalHeaderItem(3, new QTableWidgetItem("Ware"));
    _ui->_table->setHorizontalHeaderItem(4, new QTableWidgetItem("Lieferant"));
    _ui->_table->setHorizontalHeaderItem(5, new QTableWidgetItem("Feld"));
    _ui->_table->setHorizontalHeaderItem(6, new QTableWidgetItem("Brutto"));
    _ui->_table->setHorizontalHeaderItem(7, new QTableWidgetItem("Tara"));
    _ui->_table->setHorizontalHeaderItem(8, new QTableWidgetItem("Netto"));

    this->connect(_ui->_pushRefresh, SIGNAL(clicked()), this, SLOT(getAllWeightings()));
}

void WeightingView::getAllWeightings(void)
{
    if (!_database)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": no database is set.";
        return;
    }

    QVector<StoredWeighting> weightings;

    _database->getWeightings(weightings);
    _ui->_table->setRowCount(weightings.size());

    for (int row = 0; row < weightings.size(); row++)
    {
        _ui->_table->setItem(row, 0, new QTableWidgetItem(QString::number(weightings[row].id())));
        _ui->_table->setItem(row, 1, new QTableWidgetItem(weightings[row].vehicle()));
        _ui->_table->setItem(row, 2, new QTableWidgetItem(weightings[row].date().toString("yyyy.MM.dd hh:mm:ss")));
        _ui->_table->setItem(row, 3, new QTableWidgetItem(weightings[row].good()));
        _ui->_table->setItem(row, 4, new QTableWidgetItem(weightings[row].supplier()));
        _ui->_table->setItem(row, 5, new QTableWidgetItem(weightings[row].field()));
        _ui->_table->setItem(row, 6, new QTableWidgetItem(QString::number(weightings[row].brutto())));
        _ui->_table->setItem(row, 7, new QTableWidgetItem(QString::number(weightings[row].tara())));
        _ui->_table->setItem(row, 8, new QTableWidgetItem(QString::number(weightings[row].netto())));
    }
}
