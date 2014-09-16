#ifndef ___DATABASE_H___
#define ___DATABASE_H___

#include <vector>

#include <QSqlDatabase>

class Vehicle;

class Database
{
public:
    Database(void);

    bool connect(const QString& database, const QString& address = "localhost");
    void disconnect(void);

    void getAllVehicles(std::vector<Vehicle*>& vehicles);

private:
    QSqlDatabase _database;
};

#endif
