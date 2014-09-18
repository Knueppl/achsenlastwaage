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
    _database.setUserName("waage");
    _database.setDatabaseName(database);

    if (!_database.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              _database.lastError().text());

        return false;
    }

    return true;
}

void Database::disconnect(void)
{
    _database.close();
}

void Database::getAllVehicles(std::vector<Vehicle*>& vehicles)
{
    QSqlQuery query("SELECT id, name, achsen, achse_1, achse_2, achse_3, achse_4, achse_5 FROM fahrzeuge");

    while (query.next())
    {
        Vehicle* vehicle = new Vehicle;

        vehicle->setName(query.value(1).toString());
        vehicle->setNumberOfAxis(query.value(2).toInt());
        vehicle->setTara(query.value(3).toInt());
        vehicles.push_back(vehicle);
    }
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
