#include "WeightingView.h"
#include "ui_WeightingView.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

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
                  SLOT(filterHasBeenChanged(int)));
    this->connect(_ui->_comboField,
                  SIGNAL(currentIndexChanged(int)),
                  this,
                  SLOT(filterHasBeenChanged(int)));
    this->connect(_ui->_comboGood,
                  SIGNAL(currentIndexChanged(int)),
                  this,
                  SLOT(filterHasBeenChanged(int)));
    this->connect(_ui->_comboVehicle,
                  SIGNAL(currentIndexChanged(int)),
                  this,
                  SLOT(filterHasBeenChanged(int)));
    this->connect(_ui->_pushExportCsv, SIGNAL(clicked()), this, SLOT(exportCsv()));
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

    _weightings.clear();
    _database->getWeightings(_weightings);
    _ui->_table->setRowCount(_weightings.size());

    for (int row = 0; row < _weightings.size(); row++)
    {
        _ui->_table->setItem(row, 0, new QTableWidgetItem(QString::number(_weightings[row].id())));
        _ui->_table->setItem(row, 1, new QTableWidgetItem(_weightings[row].vehicle()));
        _ui->_table->setItem(row, 2, new QTableWidgetItem(_weightings[row].date().toString("yyyy.MM.dd hh:mm:ss")));
        _ui->_table->setItem(row, 3, new QTableWidgetItem(_weightings[row].good()));
        _ui->_table->setItem(row, 4, new QTableWidgetItem(_weightings[row].supplier()));
        _ui->_table->setItem(row, 5, new QTableWidgetItem(_weightings[row].field()));
        _ui->_table->setItem(row, 6, new QTableWidgetItem(QString::number(_weightings[row].brutto())));
        _ui->_table->setItem(row, 7, new QTableWidgetItem(QString::number(_weightings[row].tara())));
        _ui->_table->setItem(row, 8, new QTableWidgetItem(QString::number(_weightings[row].netto())));
    }

    // Select the last row.
    _ui->_table->selectRow(_ui->_table->rowCount() - 1);

    // Space for tests.
    this->getSuppliers ();
    this->getFields ();
    this->getGoods ();
    this->getVehicles ();
}

void WeightingView::filterHasBeenChanged(int)
{
    const QString supplier = _ui->_comboSupplier->currentIndex() > 0 ? _ui->_comboSupplier->currentText() : "";
    const QString field = _ui->_comboField->currentIndex() > 0 ? _ui->_comboField->currentText() : "";
    const QString good = _ui->_comboGood->currentIndex() > 0 ? _ui->_comboGood->currentText() : "";
    const QString vehicle = _ui->_comboVehicle->currentIndex() > 0 ? _ui->_comboVehicle->currentText() : "";
    QObject* sender = this->sender();

    if (sender == _ui->_comboSupplier)
    {
        this->getFields(supplier, good, vehicle);
        this->getGoods(supplier, field, vehicle);
        this->getVehicles(supplier, field, good);
    }
    else if (sender == _ui->_comboField)
    {
        this->getSuppliers(field, good, vehicle);
        this->getGoods(supplier, field, vehicle);
        this->getVehicles(supplier, field, good);
    }
    else if (sender == _ui->_comboGood)
    {
        this->getSuppliers(field, good, vehicle);
        this->getFields(supplier, good, vehicle);
        this->getVehicles(supplier, field, good);
    }
    else if (sender == _ui->_comboVehicle)
    {
        this->getSuppliers(field, good, vehicle);
        this->getFields(supplier, good, vehicle);
        this->getGoods(supplier, field, vehicle);
    }
}

void WeightingView::getSuppliers(const QString& field, const QString& good, const QString& vehicle)
{
   QVector<QString> suppliers;
   const QString supplier = _ui->_comboSupplier->currentText();

    this->disconnect(_ui->_comboSupplier, SIGNAL(currentIndexChanged(int)), this, SLOT(filterHasBeenChanged(int)));
   _database->getSuppliersFromWeightings(suppliers, field, good, vehicle);
   _ui->_comboSupplier->clear();
   _ui->_comboSupplier->addItem("Lieferant");

   for (auto& supplier : suppliers)
      _ui->_comboSupplier->addItem(supplier);

   for (int item = 0; item < _ui->_comboSupplier->count(); ++item)
   {
       if (supplier == _ui->_comboSupplier->itemText(item))
       {
           _ui->_comboSupplier->setCurrentIndex(item);
           break;
       }
   }

   this->connect(_ui->_comboSupplier, SIGNAL(currentIndexChanged(int)), this, SLOT(filterHasBeenChanged(int)));
}

void WeightingView::getFields(const QString& supplier, const QString& good, const QString& vehicle)
{
   QVector<QString> fields;
   const QString field = _ui->_comboField->currentText();

    this->disconnect(_ui->_comboField, SIGNAL(currentIndexChanged(int)), this, SLOT(filterHasBeenChanged(int)));
   _database->getFieldsFromWeightings (fields, supplier, good, vehicle);
   _ui->_comboField->clear();
   _ui->_comboField->addItem("Feld");

   for (auto& field : fields)
      _ui->_comboField->addItem(field);

   for (int item = 0; item < _ui->_comboField->count(); ++item)
   {
       if (field == _ui->_comboField->itemText(item))
       {
           _ui->_comboField->setCurrentIndex(item);
           break;
       }
   }

   this->connect(_ui->_comboField, SIGNAL(currentIndexChanged(int)), this, SLOT(filterHasBeenChanged(int)));
}

void WeightingView::getGoods(const QString& supplier, const QString& field, const QString& vehicle)
{
   QVector<QString> goods;
   const QString good = _ui->_comboGood->currentText();

    this->disconnect(_ui->_comboGood, SIGNAL(currentIndexChanged(int)), this, SLOT(filterHasBeenChanged(int)));
   _database->getGoodsFromWeightings(goods, supplier, field, vehicle);
   _ui->_comboGood->clear();
   _ui->_comboGood->addItem("Ware");

   for (auto& good : goods)
      _ui->_comboGood->addItem(good);

   for (int item = 0; _ui->_comboGood->count(); ++item)
   {
       if (good == _ui->_comboGood->itemText(item))
       {
           _ui->_comboGood->setCurrentIndex(item);
           break;
       }
   }

   this->connect(_ui->_comboGood, SIGNAL(currentIndexChanged(int)), this, SLOT(filterHasBeenChanged(int)));
}

void WeightingView::getVehicles(const QString& supplier, const QString& field, const QString& good)
{
   QVector<QString> vehicles;
   const QString vehicle = _ui->_comboVehicle->currentText();

    this->disconnect(_ui->_comboVehicle, SIGNAL(currentIndexChanged(int)), this, SLOT(filterHasBeenChanged(int)));
   _database->getVehiclesFromWeightings (vehicles, supplier, field, good);
   _ui->_comboVehicle->clear();
   _ui->_comboVehicle->addItem("Fahrzeug");

   for (auto& vehicle : vehicles)
      _ui->_comboVehicle->addItem(vehicle);

   for (int item = 0; item < _ui->_comboVehicle->count(); ++item)
   {
       if (vehicle == _ui->_comboVehicle->itemText(item))
       {
           _ui->_comboVehicle->setCurrentIndex(item);
           break;
       }
   }

   this->connect(_ui->_comboVehicle, SIGNAL(currentIndexChanged(int)), this, SLOT(filterHasBeenChanged(int)));
}

void WeightingView::exportCsv(void)
{
    const QString fileName(QFileDialog::getSaveFileName(this,
                                                        "Wählen Sie bitte einen Dateinamen aus.",
                                                        "~/"
                                                        "*.csv"));

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(0, "Dateifehler", QString("Kann die Datei ") + fileName + QString(" nicht öffnen"));
        return;
    }

    QTextStream out(&file);
    out << "Wiegung; Fahrzeug; Datum/Uhrzeit; Ware; Lieferant; Feld; Brutto; Tara; Netto\n";

    for (auto& weighting : _weightings)
    {
        out << weighting.id() << "; " << weighting.vehicle() << "; "
            << weighting.date().toString("yyyy:MM:dd hh:mm:ss") << "; " << weighting.good() << "; "
            << weighting.supplier() << "; " << weighting.field() << "; " << weighting.brutto() << "; "
            << weighting.tara() << "; " << weighting.netto() << "\n";
    }

    file.close();
}
