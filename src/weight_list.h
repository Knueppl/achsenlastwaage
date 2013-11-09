#ifndef _WEIGHT_LIST_H_
#define _WEIGHT_LIST_H_

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QDateTime>

const int numberOfAxis = 5;

class Weight : public QListWidgetItem
{
public:
    Weight(const QString& vehicle = QString(), const int tara = 0, const int numberOfAxis = 0,
           const QString& product = QString(), const QString& supplier = QString(), QListWidget* parent = 0, int type = Type);
    ~Weight(void);

    const QString& vehicle(void) const { return m_vehicle; }
    const QString& product(void) const { return m_product; }
    const QString& supplier(void) const { return m_supplier; }
    int brutto(void) const { return m_brutto; }
    int tara(void) const { return m_tara; }
    int netto(void) const { return m_netto; }
    int weightNoteNumber(void) const { return m_weightNoteNumber; }
    bool axisState(const int axis) const { return m_axisState[axis]; }
    int numberOfAxis(void) const { return m_numberOfAxis; }
    const QDateTime& dateTime(void) const { return m_dateTime; }
    int axis(const int axis) const { return m_axis[axis]; }
    const QString& date(void) const { return m_date; }

    int addAxis(const int weight, const bool state = true);
    void setWeightNoteNumber(const int weightNoteNumber) { m_weightNoteNumber = weightNoteNumber; }
    void setVehicle(const QString& vehicle) { m_vehicle = vehicle; }
    void setProduct(const QString& product) { m_product = product; }
    void setSupplier(const QString& supplier) { m_supplier = supplier; }
    void setTara(const int tara) { m_tara = tara; }
    void setBrutto(const int brutto) { m_brutto = brutto; }
    void setNetto(const int netto) { m_netto = netto; }
    void setDate(const QString& date) { m_date = date; }

private:
    int       m_brutto;
    int       m_tara;
    int       m_netto;
    int       m_weightNoteNumber;
    QString   m_vehicle;
    QString   m_product;
    QString   m_supplier;
    QString   m_date;
    int       m_numberOfAxis;
    bool*     m_axisState;
    int*      m_axis;
    QDateTime m_dateTime;
};

class WeightView : public QWidget
{
public:
    WeightView(const Weight* weight, QWidget* parent = 0);
    ~WeightView(void);

private:
    QHBoxLayout* m_firstRow;
    QVBoxLayout* m_layout;
    QHBoxLayout* m_axisLayout;
    QLabel**     m_axisState;
    QLabel*      m_vehicle;
    QGridLayout* m_secondRow;
    QLabel*      m_brutto;
    QLabel*      m_tara;
    QLabel*      m_netto;
    QLabel*      m_date;
    QLabel*      m_time;
};

class WeightList : public QWidget
{
    Q_OBJECT

public:
    WeightList(QWidget* parent = 0);
    ~WeightList(void);

public slots:
    void addWeight(Weight* weight, QWidget* view);

private:
    QListWidget* m_listWidget;
    QVBoxLayout* m_mainLayout;
};

class WeightHandler
{
public:
    WeightHandler(const QString& workingDirectory);

    void saveWeightToFile(const Weight* weight) const;
    Weight* loadWeightFromFile(void) const;

private:
    QString m_workingDirectory;
};

#endif
