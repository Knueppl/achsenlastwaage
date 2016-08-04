#ifndef ___STORED_WEIGHTING_H___
#define ___STORED_WEIGHTING_H___

#include <QString>
#include <QDateTime>

class StoredWeighting
{
public:
    StoredWeighting(void)
        : _id(-1),
          _vehicle("none"),
          _brutto(-1),
          _tara(-1),
          _netto(-1)
    {

    }

    StoredWeighting(const int id,
                    const QString& vehicle,
                    const QDateTime& date,
                    const QString& good,
                    const QString& supplier,
                    const QString& field,
                    const int brutto,
                    const int tara,
                    const int netto)
        : _id(id),
          _vehicle(vehicle),
          _date(date),
          _good(good),
          _supplier(supplier),
          _field(field),
          _brutto(brutto),
          _tara(tara),
          _netto(netto)
    {

    }

    int id(void) const { return _id; }
    const QString& vehicle(void) const { return _vehicle; }
    const QDateTime& date(void) const { return _date; }
    const QString& good(void) const { return _good; }
    const QString& supplier(void) const { return _supplier; }
    const QString& field(void) const { return _field; }
    int brutto(void) const { return _brutto; }
    int tara(void) const { return _tara; }
    int netto(void) const { return _netto; }

private:
    int _id;
    QString _vehicle;
    QDateTime _date;
    QString _good;
    QString _supplier;
    QString _field;
    int _brutto;
    int _tara;
    int _netto;
};

#endif
