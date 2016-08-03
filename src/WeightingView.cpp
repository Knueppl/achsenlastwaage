#include "WeightingView.h"
#include "ui_WeightingView.h"

#include <QDebug>

WeightingView::WeightingView(QWidget* parent)
    : QWidget(parent),
      _ui(new Ui::WeightingView),
      _database(0)
{
    _ui->setupUi(this);
    _ui->_table->setColumnCount(6);

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
        _ui->_table->setItem(row, 3, new QTableWidgetItem(QString::number(weightings[row].brutto())));
        _ui->_table->setItem(row, 4, new QTableWidgetItem(QString::number(weightings[row].tara())));
        _ui->_table->setItem(row, 5, new QTableWidgetItem(QString::number(weightings[row].netto())));
    }
}
