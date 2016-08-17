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
    this->connect(_ui->_comboSupplier,
                  SIGNAL(currentIndexChanged(int)),
                  this,
                  SLOT(supplierFilterHasBeenChanged(int)));
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
   this->getSuppliers ();
   this->getFields ();
   this->getGoods ();
   this->getVehicles ();
}

void WeightingView::supplierFilterHasBeenChanged (int)
{
   const QString supplier = _ui->_comboSupplier->currentIndex() > 0 ? _ui->_comboSupplier->currentText() : "";
   const QString field = _ui->_comboField->currentIndex() > 0 ? _ui->_comboField->currentText() : "";
   const QString good = _ui->_comboGood->currentIndex() > 0 ? _ui->_comboGood->currentText() : "";
   const QString vehicle = _ui->_comboVehicle->currentIndex() > 0 ? _ui->_comboVehicle->currentText() : "";

   if (!_ui->_comboField->currentIndex())
      this->getFields (supplier, good, vehicle);
   if (!_ui->_comboGood->currentIndex())
      this->getGoods (supplier, field, vehicle);
   if (!_ui->_comboVehicle->currentIndex())
      this->getVehicles (supplier, field, good);
}

void WeightingView::getSuppliers(const QString& field, const QString& good, const QString& vehicle)
{
   qDebug() << __PRETTY_FUNCTION__;
   qDebug() << field << good << vehicle;
   QVector<QString> suppliers;

   _database->getSuppliersFromWeightings(suppliers, field, good, vehicle);

   _ui->_comboSupplier->clear();
   _ui->_comboSupplier->addItem("Lieferant");

   for (auto& supplier : suppliers)
      _ui->_comboSupplier->addItem(supplier);
}

void WeightingView::getFields(const QString& supplier, const QString& good, const QString& vehicle)
{
   QVector<QString> fields;

   _database->getFieldsFromWeightings (fields, supplier, good, vehicle);
   _ui->_comboField->clear();
   _ui->_comboField->addItem("Feld");


   for (auto& field : fields)
      _ui->_comboField->addItem(field);
}

void WeightingView::getGoods(const QString& supplier, const QString& field, const QString& vehicle)
{
   QVector<QString> goods;

   _database->getGoodsFromWeightings(goods, supplier, field, vehicle);
   _ui->_comboGood->clear();
   _ui->_comboGood->addItem("Ware");

   for (auto& good : goods)
      _ui->_comboGood->addItem(good);
}

void WeightingView::getVehicles(const QString& supplier, const QString& field, const QString& good)
{
   QVector<QString> vehicles;

   _database->getVehiclesFromWeightings (vehicles, supplier, field, good);
   _ui->_comboVehicle->clear();
   _ui->_comboVehicle->addItem("Fahrzeug");

   for (auto& vehicle : vehicles)
      _ui->_comboVehicle->addItem(vehicle);
}
