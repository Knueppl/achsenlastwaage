#include "Database.h"
#include "Vehicle.h"
#include "Weighting.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QTextStream>

Database::Database(void)
{
    this->connect("information_schema");
}

bool Database::connect(const QString& database, const QString& address)
{
    this->disconnect();

    _database = QSqlDatabase::addDatabase("QMYSQL");
    _database.setHostName(address);
    _database.setUserName("wiegemeister");
    _database.setPassword("1234");

    return this->selectDatabase(database);
}

void Database::disconnect(void)
{
    _database.close();
}

bool Database::selectDatabase(const QString& database)
{
    _database.close();
    _database.setDatabaseName(database);

    if (!_database.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"), _database.lastError().text());
        return false;
    }
}

QVector<QString> Database::databases(void)
{
    QSqlQuery query("SHOW DATABASES", _database);
    QVector<QString> bases;

    while (query.next())
        bases.push_back(query.value(0).toString());

    return bases;
}

void Database::createDatabase(const QString& database)
{
    // Create a new database itself.
    QSqlQuery query(_database);

    query.prepare(QString("CREATE DATABASE ") + database);

    if (!query.exec())
        QMessageBox::critical(0, "Database Error", query.lastError().text());

    this->selectDatabase(database);


    // Create the table vehicles.
    query.prepare("CREATE TABLE fahrzeuge ("
                  "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                  "name VARCHAR(100) NOT NULL,"
                  "tara INT,"
                  "achsen INT NOT NULL"
                  ")");

    if (!query.exec())
        QMessageBox::critical(0, "Database Error", query.lastError().text());


    // Create the table goods.
    query.prepare("CREATE TABLE waren ("
                  "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                  "name VARCHAR(100) NOT NULL UNIQUE"
                  ")");

    if (!query.exec())
        QMessageBox::critical(0, "Database Error", query.lastError().text());


    // Create the table supplier.
    query.prepare("CREATE TABLE lieferanten ("
                  "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                  "name VARCHAR(100) NOT NULL UNIQUE"
                  ")");

    if (!query.exec())
        QMessageBox::critical(0, "Database Error", query.lastError().text());


    // Create the table weighting.
    query.prepare("CREATE TABLE wiegungen ("
                  "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                  "fahrzeug INT NOT NULL,"
                  "ware INT,"
                  "lieferant INT,"
                  "feld INT,"
                  "datum TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,"
                  "brutto INT,"
                  "tara INT,"
                  "netto INT"
                  ")");

    if (!query.exec())
        QMessageBox::critical(0, "Database Error", query.lastError().text());


    // Create the table field.
    query.prepare("CREATE TABLE felder ("
                  "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                  "name VARCHAR(100) NOT NULL UNIQUE"
                  ")");

    if (!query.exec())
        QMessageBox::critical(0, "Database Error", query.lastError().text());


    // Add some default goods.
//    this->addGood("Mais");
//    this->addGood("Triticale");

    // Add a default supplier.
//    this->addSupplier("Merkl");
}

void Database::save(const QString& fileName)
{
    QSqlQuery query(_database);
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(0,
                              "Database Error",
                              QString("Kann die Datei ") + fileName + QString(" nicht öffnen."));
        return;
    }

    QTextStream out(&file);

    query.prepare("SELECT id, name, tara, achsen FROM fahrzeuge");
    out << "Fahrzeuge:\n";

    while (query.next())
    {
        out << query.value(0).toString() << "; " << query.value(1).toString() << "; "
            << query.value(2).toString() << "; " << query.value(3).toString() << "\n";
    }
}

void Database::load(const QString& fileName)
{

}

void Database::drop(void)
{

}

void Database::getAllVehicles(QVector<Vehicle*>& vehicles)
{
    QSqlQuery query(_database);

    query.prepare("SELECT id, name, achsen, tara FROM fahrzeuge");

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann die Fahrzeug nicht aus der Datenbank lesen.");
    }

    while (query.next())
    {
        vehicles.push_back(new Vehicle(query.value(0).toInt(),
                                       query.value(1).toString(),
                                       query.value(2).toInt(),
                                       query.value(3).toInt()));
    }
}

void Database::addVehicle(Vehicle* vehicle)
{
    QSqlQuery query(_database);

    query.prepare("INSERT INTO fahrzeuge (name, tara, achsen) VALUES (?, ?, ?)");
    query.bindValue(0, vehicle->name());
    query.bindValue(1, vehicle->tara());
    query.bindValue(2, vehicle->axes());

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann das Fahrzeug nicht zur Datenbank hinzufügen.");
        return;
    }

    query.prepare(QString("SELECT id FROM fahrzeuge WHERE name = \"") + vehicle->name() + "\"");

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann die des Fahrzeuges nicht ermitteln.");
        return;
    }

    query.next();
    vehicle->setId(query.value(0).toInt());
}

void Database::getAllGoods(QVector<QString>& goods)
{
    QSqlQuery query(_database);

    goods.clear();
    query.prepare("SELECT name FROM waren ORDER BY id");

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann die Waren nicht aus der Datenbank lesen.");
    }

    while (query.next())
        goods.push_back(query.value(0).toString());
}

void Database::addGood(const QString& good)
{
    QSqlQuery query(_database);

    query.prepare("INSERT INTO waren (name) VALUES (?)");
    query.bindValue(0, good);

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann die Ware nicht zur Datenbank hinzufügen.");
    }
}

void Database::getAllSuppliers(QVector<QString>& suppliers)
{
    QSqlQuery query(_database);

    suppliers.clear();
    query.prepare("SELECT name FROM lieferanten ORDER BY id");

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann die Lieferanten nicht aus der Datenbank lesen.");
    }

    while (query.next())
        suppliers.push_back(query.value(0).toString());
}

void Database::addSupplier(const QString& supplier)
{
    QSqlQuery query(_database);

    query.prepare("INSERT INTO lieferanten (name) VALUES (?)");
    query.bindValue(0, supplier);

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann den Lieferanten nicht zur Datenbank hinzufügen.");
    }
}

void Database::getAllFields(QVector<QString>& fields)
{
    QSqlQuery query(_database);

    fields.clear();
    query.prepare("SELECT name FROM felder ORDER BY id");

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann die Felder nicht aus der Datenbank lesen.");
    }

    while (query.next())
        fields.push_back(query.value(0).toString());
}

void Database::addField(const QString& field)
{
    QSqlQuery query(_database);

    query.prepare("INSERT INTO felder (name) VALUES (?)");
    query.bindValue(0, field);

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann das Feld nicht zur Datenbank hinzufügen.");
    }
}

void Database::addWeighting(const Weighting* weighting)
{
    QSqlQuery query(_database);

    query.prepare("INSERT INTO wiegungen (fahrzeug, ware, lieferant, feld, brutto, tara, netto)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, weighting->vehicle()->id());
    query.bindValue(1, weighting->goodId());
    query.bindValue(2, weighting->supplierId());
    query.bindValue(3, weighting->fieldId());
    query.bindValue(4, weighting->brutto());
    query.bindValue(5, weighting->tara());
    query.bindValue(6, weighting->netto());

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann die Wiegung nicht zur Datenbank hinzufügen.");
    }
}

void Database::getWeightings(QVector<StoredWeighting>& weightings)
{
    QSqlQuery query(_database);

    query.prepare("SELECT "
                  "wiegungen.id, "
                  "fahrzeuge.name, "
                  "wiegungen.datum, "
                  "waren.name, "
                  "lieferanten.name, "
                  "felder.name, "
                  "wiegungen.brutto, "
                  "wiegungen.tara, "
                  "wiegungen.netto "
                  "FROM "
                  "wiegungen, fahrzeuge, lieferanten, felder, waren "
                  "WHERE "
                  "wiegungen.fahrzeug = fahrzeuge.id AND "
                  "wiegungen.ware = waren.id AND "
                  "wiegungen.lieferant = lieferanten.id AND "
                  "wiegungen.feld = felder.id "
                  "ORDER BY wiegungen.id");

    if (!query.exec())
    {
        qDebug() << query.lastError();
        QMessageBox::critical(0, "Database Error", "Kann die Wiegungnen nicht von der Datenbank lesen.");
        return;
    }

    while (query.next())
    {
        weightings.push_back(StoredWeighting(query.value(0).toInt(),
                                             query.value(1).toString(),
                                             QDateTime::fromString(query.value(2).toString(),
                                                                   "yyyy-MM-ddThh:mm:ss"),
                                             query.value(3).toString(),
                                             query.value(4).toString(),
                                             query.value(5).toString(),
                                             query.value(6).toInt(),
                                             query.value(7).toInt(),
                                             query.value(8).toInt()));
    }
}
