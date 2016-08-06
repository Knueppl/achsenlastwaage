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

void WeightingView::setDatabase (Database &database)
{
   _database = &database;

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

   // Space for tests.
   this->getSuppliers (-1, -1, -1);
   this->getFields (-1, -1, -1);
   this->getGoods (-1, -1, -1);
   this->getVehicles (-1, -1, -1);
}

void WeightingView::getSuppliers(const int fieldId, const int goodId, const int vehicleId)
{
   QVector<QString> suppliers;

   _database->getSuppliersFromWeightings(suppliers, fieldId, goodId, vehicleId);

   _ui->_comboSupplier->clear();

   for (auto& supplier : suppliers)
      _ui->_comboSupplier->addItem(supplier);

   _ui->_comboSupplier->addItem("Lieferant");
}

void WeightingView::getFields(const int supplierId, const int goodId, const int vehicleId)
{
   QVector<QString> fields;

   _database->getFieldsFromWeightings (fields, supplierId, goodId, vehicleId);
   _ui->_comboField->clear();

   for (auto& field : fields)
      _ui->_comboField->addItem(field);

   _ui->_comboField->addItem("Feld");
}

void WeightingView::getGoods(const int supplierId, const int fieldId, const int vehicleId)
{
   QVector<QString> goods;

   _database->getGoodsFromWeightings(goods, supplierId, fieldId, vehicleId);
   _ui->_comboGood->clear();

   for (auto& good : goods)
      _ui->_comboGood->addItem(good);

   _ui->_comboGood->addItem("Ware");
}

void WeightingView::getVehicles(const int supplierId, const int fieldId, const int goodId)
{
   QVector<QString> vehicles;

   _database->getVehiclesFromWeightings (vehicles, supplierId, fieldId, goodId);
   _ui->_comboVehicle->clear();

   for (auto& vehicle : vehicles)
      _ui->_comboVehicle->addItem(vehicle);

   _ui->_comboVehicle->addItem("Fahrzeug");
}
