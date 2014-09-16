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
    QSqlQuery query("SELECT * FROM wiegungen");
     while (query.next()) {
         QString country = query.value(0).toString();
         qDebug() << country;
     }
}
