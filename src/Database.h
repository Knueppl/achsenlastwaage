#ifndef ___DATABASE_H___
#define ___DATABASE_H___

#include <QVector>
#include <QSqlDatabase>

class Vehicle;
class Weighting;

class Database
{
public:
    Database(void);

    bool connect(const QString& database, const QString& address = "localhost");
    void disconnect(void);
    bool selectDatabase(const QString& database);
    QVector<QString> databases(void);

    void createDatabase(const QString& database);
    void save(const QString& fileName);
    void load(const QString& fileName);
    void drop(void);

    void getAllVehicles(QVector<Vehicle*>& vehicles);
    void addVehicle(const Vehicle* vehicle);

    void getAllGoods(QVector<QString>& goods);
    void addGood(const QString& good);

    void getAllSuppliers(QVector<QString>& suppliers);
    void addSupplier(const QString& supplier);

    void getAllFields(QVector<QString>& fields);
    void addField(const QString& field);

    void addWeighting(const Weighting* weighting);

private:
    QSqlDatabase _database;
};

#endif
