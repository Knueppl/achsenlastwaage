#include "Database.h"
#include "Vehicle.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Database::Database(void)
{

}

bool Database::connect(const QString& database, const QString& address)
{
    _database = QSqlDatabase::addDatabase("QMYSQL");
    _database.setHostName(address);
    _database.setUserName("wiegemeister");
    _database.setPassword("1234");
    _database.setDatabaseName(database);

    if (!_database.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"), _database.lastError().text());
        return false;
    }

    return true;
}

void Database::disconnect(void)
{
    _database.close();
}

void Database::create(void)
{
    QSqlQuery query("CREATE TABLE fahrzeuge ("
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

}

void Database::load(const QString& fileName)
{

}

void Database::drop(void)
{

}

void Database::getAllVehicles(std::vector<Vehicle*>& vehicles)
{
    QSqlQuery query("SELECT id, name, achsen FROM fahrzeuge");

    while (query.next())
        vehicles.push_back(new Vehicle(query.value(1).toString(), query.value(2).toInt(), query.value(3).toInt()));
}

void Database::addVehicle(const Vehicle* vehicle)
{
    QSqlQuery query;

    query.prepare("INSERT INTO fahrzeuge (name, tara, achsen) VALUES (?, ?, ?)");
    query.bindValue(0, vehicle->name());
    query.bindValue(1, vehicle->tara());
    query.bindValue(2, vehicle->numberOfAxis());

    if (!query.exec())
    {
        QMessageBox::critical(0, "Database Error", "Kann das Fahrzeug nicht zur Datenbank hinzufügen.");
    }
}
