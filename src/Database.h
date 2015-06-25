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
    QVector<QString> databases(void);

    void create(void);
    void save(const QString& fileName);
    void load(const QString& fileName);
    void drop(void);

    void getAllVehicles(std::vector<Vehicle*>& vehicles);
    void addVehicle(const Vehicle* vehicle);

private:
    QSqlDatabase _database;
};

#endif
