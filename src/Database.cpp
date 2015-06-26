#include "Database.h"
#include "Vehicle.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QTextStream>

Database::Database(void)
{

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
    QSqlQuery query(_database);

    query.prepare(QString("CREATE DATABASE ") + database);

    if (!query.exec())
        QMessageBox::critical(0, "Database Error", query.lastError().text());

    this->selectDatabase(database);

    query.prepare("CREATE TABLE fahrzeuge ("
                  "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                  "name VARCHAR(100) NOT NULL,"
                  "tara INT,"
                  "achsen INT NOT NULL"
                  ")");

    if (!query.exec())
        QMessageBox::critical(0, "Database Error", query.lastError().text());
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

void Database::getAllVehicles(std::vector<Vehicle*>& vehicles)
{
    QSqlQuery query("SELECT id, name, achsen FROM fahrzeuge", _database);

    while (query.next())
        vehicles.push_back(new Vehicle(query.value(1).toString(), query.value(2).toInt(), query.value(3).toInt()));
}

void Database::addVehicle(const Vehicle* vehicle)
{
    QSqlQuery query(_database);

    query.prepare("INSERT INTO fahrzeuge (name, tara, achsen) VALUES (?, ?, ?)");
    query.bindValue(0, vehicle->name());
    query.bindValue(1, vehicle->tara());
    query.bindValue(2, vehicle->numberOfAxis());

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann das Fahrzeug nicht zur Datenbank hinzufügen.");
    }
}
