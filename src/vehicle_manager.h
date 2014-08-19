#ifndef _VEHICLE_MANAGER_H_
#define _VEHICLE_MANAGER_H_

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QString>
#include <QList>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QListWidget>
#include <QComboBox>
#include <QCheckBox>

#include "fzw12.h"


class ProductsAndSuppliers : public QGroupBox
{
    Q_OBJECT;

public:
    ProductsAndSuppliers(QWidget* parent = 0);

    QString product(void) const { return m_products->currentText(); }
    QString supplier(void) const { return m_suppliers->currentText(); }

public slots:
    void editSupplier(void);
    void editProducts(void);

private:
    void loadProductsFromFile(void);
    void loadSuppliersFromFile(void);

    QGridLayout*  m_mainLayout;
    QComboBox*    m_products;
    QComboBox*    m_suppliers;
    QLabel*       m_infoProduct;
    QLabel*       m_infoSupplier;
    QPushButton*  m_editProduct;
    QPushButton*  m_editSupplier;
};

class Vehicle
{
public:
    Vehicle(void) : m_numberOfAxis(0), m_tara(0) { }

    void setName(const QString& name) { m_name = name; }
    void setNumberOfAxis(const int numberOfAxis) { m_numberOfAxis = numberOfAxis; }
    void setTara(const int tara) { m_tara = tara; }
    void setButton(QPushButton* button) { m_button = button; }
    void setAction(QAction* action) { m_action = action; }
    const QString& name(void) const { return m_name; }
    int numberOfAxis(void) const { return m_numberOfAxis; }
    int tara(void) const { return m_tara; }
    QPushButton* button(void) const { return m_button; }
    QAction* action(void) const { return m_action; }

private:
    QString      m_name;
    int          m_numberOfAxis;
    int          m_tara;
    QPushButton* m_button;
    QAction*     m_action;
};

class Control;

class VehicleManager : public QWidget
{
    Q_OBJECT;

public:
    VehicleManager(Control* control, QWidget* parent = 0);
    ~VehicleManager(void);

    void addVehicle(Vehicle* vehicle);
    void removeVehicle(Vehicle* vehicle);
    void loadFromFile(const QString& filename);
    void saveToFile(const QString& filename);
    bool weightNoteEnable(void) const { return m_productsAndSuppliers->isChecked(); }
    const QList<Vehicle*> vehicles(void) const { return m_vehicles; }

public slots:
    void createVehicle(void);
    void deleteVehicle(void);
    void abortWeighting(void);
    void finishWeight(void);

private slots:
    void startWeighting(void);

private:
    Control*              m_control;
    QVBoxLayout*          m_vehicleLayout;
    QGridLayout*          m_optionLayout;
    QHBoxLayout*          m_mainLayout;
    QGroupBox*            m_groupVehicle;
    QGroupBox*            m_groupOption;
    QGroupBox*            m_groupWeightNote;
    QList<Vehicle*>       m_vehicles;
    QPushButton*          m_createVehicle;
    QPushButton*          m_deleteVehicle;
    QPushButton*          m_abortWeighting;
    ProductsAndSuppliers* m_productsAndSuppliers;
    SignalLight*          m_signalLight;
};

class CreateVehicleDialog : public QDialog
{
    Q_OBJECT;

public:
    CreateVehicleDialog(VehicleManager* manager, QWidget* parent = 0);

private slots:
    void updateAxis(int);
    void createVehicle(void);

private:
    VehicleManager* m_manager;

    QPushButton*    m_accept;
    QPushButton*    m_abort;
    QHBoxLayout*    m_firstRow;
    QHBoxLayout*    m_secondRow;
    QHBoxLayout*    m_thirdRow;
    QHBoxLayout*    m_fourthRow;
    QLineEdit*      m_name;
    QSlider*        m_numberOfAxis;
    QSpinBox*       m_tara;
    QVBoxLayout*    m_mainLayout;
    QList<QLabel*>  m_axis;
    QLabel*         m_info1;
    QLabel*         m_info2;
};

class DeleteVehicleDialog : public QDialog
{
    Q_OBJECT;

public:
    DeleteVehicleDialog(VehicleManager* manager, QWidget* parent = 0);

private slots:
    void deleteVehicle(void);

private:
    void updateList(void);

    VehicleManager* m_manager;
    QVBoxLayout*    m_mainLayout;
    QListWidget*    m_list;
    QHBoxLayout*    m_buttonLayout;
    QPushButton*    m_delete;
    QPushButton*    m_close;
};

#endif
