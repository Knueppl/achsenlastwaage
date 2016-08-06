#ifndef ___DATABASE_H___
#define ___DATABASE_H___

#include <QVector>
#include <QSqlDatabase>

#include "StoredWeighting.h"

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
    void addVehicle(Vehicle* vehicle);

    void getAllGoods(QVector<QString>& goods);
    void addGood(const QString& good);

    void getAllSuppliers(QVector<QString>& suppliers);
    void addSupplier(const QString& supplier);

    void getAllFields(QVector<QString>& fields);
    void addField(const QString& field);

    void addWeighting(const Weighting* weighting);
    void getWeightings(QVector<StoredWeighting>& weightings);
    void getSuppliersFromWeightings(QVector<QString>& suppliers,
				    const int fieldId,
				    const int goodId,
				    const int vehicleId);
    void getGoodsFromWeightings(QVector<QString>& goods,
				const int supplierId,
				const int fieldId,
				const int vehicleId);
    void getFieldsFromWeightings(QVector<QString>& fields,
				 const int supplierId,
				 const int goodId,
				 const int vehicleId);
    void getVehiclesFromWeightings(QVector<QString>& vehicles,
				   const int supplierId,
				   const int fieldId,
				   const int goodId);

private:
    QSqlDatabase _database;
};

#endif
