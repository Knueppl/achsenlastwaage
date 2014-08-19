#include "vehicle_manager.h"
#include "SupplierDialog.h"
#include "ProductDialog.h"

#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QShortcut>
#include "control.h"

VehicleManager::VehicleManager(Control* control, QWidget* parent) : QWidget(parent)
{
    m_control = control;
    m_mainLayout = new QHBoxLayout(this);

    m_groupVehicle = new QGroupBox("Fahrzeuge");
    m_groupVehicle->setMinimumWidth(200);
    m_vehicleLayout = new QVBoxLayout;
    m_vehicleLayout->addStretch();
    m_groupVehicle->setLayout(m_vehicleLayout);
    m_mainLayout->addWidget(m_groupVehicle);

    m_groupOption = new QGroupBox("Optionen");
    m_optionLayout = new QGridLayout;
    m_optionLayout->setAlignment(Qt::AlignTop);
    m_createVehicle = new QPushButton("Neues Fahrzeug");
    m_optionLayout->addWidget(m_createVehicle, 0, 0);
    m_deleteVehicle = new QPushButton("Lösche Fahrzeug");
    m_optionLayout->addWidget(m_deleteVehicle, 0, 1);
    m_abortWeighting = new QPushButton("Abruch");
    m_abortWeighting->setEnabled(false);
    m_optionLayout->addWidget(m_abortWeighting, 2, 0);
    m_groupOption->setLayout(m_optionLayout);

    m_productsAndSuppliers = new ProductsAndSuppliers;
    QVBoxLayout* tmpLayout = new QVBoxLayout;
    tmpLayout->addWidget(m_groupOption);
    tmpLayout->addWidget(m_productsAndSuppliers);
    m_signalLight = new SignalLight("/dev/ttyACM0");
    tmpLayout->addWidget(m_signalLight);
    tmpLayout->addStretch();
    m_mainLayout->addLayout(tmpLayout);

    connect(m_createVehicle, SIGNAL(clicked()), this, SLOT(createVehicle()));
    connect(m_deleteVehicle, SIGNAL(clicked()), this, SLOT(deleteVehicle()));
    connect(m_abortWeighting, SIGNAL(clicked()), this, SLOT(abortWeighting()));

    connect(new QShortcut(QKeySequence("ESC"), this), SIGNAL(activated()), this, SLOT(abortWeighting()));
}

VehicleManager::~VehicleManager(void)
{
    while (!m_vehicles.isEmpty())
    {
        delete m_vehicles.takeFirst();
    }
}

void VehicleManager::addVehicle(Vehicle* vehicle)
{
    m_vehicles.push_front(vehicle);
    m_vehicleLayout->insertWidget(0, vehicle->button());
    connect(vehicle->button(), SIGNAL(pressed()), this, SLOT(startWeighting()));

    this->saveToFile("vehicles");
}

void VehicleManager::createVehicle(void)
{
    CreateVehicleDialog dialog(this);
    dialog.exec();
}

void VehicleManager::removeVehicle(Vehicle* vehicle)
{
    m_vehicleLayout->removeWidget(vehicle->button());
    disconnect(vehicle->button(), SIGNAL(pressed()), this, SLOT(startWeighting()));
    delete vehicle->button();
    m_vehicles.removeOne(vehicle);
    delete vehicle;

    this->saveToFile("vehicles");
}

void VehicleManager::deleteVehicle(void)
{
    DeleteVehicleDialog dialog(this);
    dialog.exec();
}

void VehicleManager::loadFromFile(const QString& filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Fehler beim öffnen der Datei: " << filename;
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line(in.readLine());
        QStringList list(line.split(":"));
        Vehicle* vehicle = new Vehicle;

        vehicle->setName(list.at(0));
        vehicle->setNumberOfAxis(list.at(1).toInt());
        vehicle->setTara(list.at(2).toInt());
        vehicle->setButton(new QPushButton(vehicle->name()));

        this->addVehicle(vehicle);
    }

    file.close();
}

void VehicleManager::saveToFile(const QString& filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Fehler beim öffnen der Datei: " << filename;
        return;
    }

    QTextStream out(&file);

    for (int i = m_vehicles.size() - 1; i >= 0; i--)
    {
        out << m_vehicles.at(i)->name() << ':';
        out << m_vehicles.at(i)->numberOfAxis() << ':';
        out << m_vehicles.at(i)->tara() << '\n';
    }

    file.close();
}

void VehicleManager::startWeighting(void)
{
    for (int i = 0; i < m_vehicles.size(); i++)
    {
        if (m_vehicles.at(i)->button()->isDown())
        {
            m_abortWeighting->setEnabled(true);

            QString product, supplier;
            if (m_productsAndSuppliers->isChecked())
            {
                product.append(m_productsAndSuppliers->product());
                supplier.append(m_productsAndSuppliers->supplier());
            }

            m_control->startWeighting(new Weight(m_vehicles.at(i)->name(),
                                                 m_vehicles.at(i)->tara(),
                                                 m_vehicles.at(i)->numberOfAxis(),
                                                 product, supplier));

            qDebug() << m_vehicles.at(i)->name() << "is pressed";
        }
        else
        {
            m_vehicles.at(i)->button()->setEnabled(false);
        }
    }

    if (m_signalLight->isEnabled())
    {
        m_signalLight->green();
    }
}

void VehicleManager::abortWeighting(void)
{
    for (int i = 0; i < m_vehicles.size(); i++)
    {
        m_vehicles.at(i)->button()->setEnabled(true);
    }

    m_abortWeighting->setEnabled(false);
    m_control->abortWeighting();

    if (m_signalLight->isEnabled())
    {
        m_signalLight->red();
    }
}

void VehicleManager::finishWeight(void)
{
    for (int i = 0; i < m_vehicles.size(); i++)
    {
        m_vehicles.at(i)->button()->setEnabled(true);
    }

    m_abortWeighting->setEnabled(false);

    if (m_signalLight->isEnabled())
    {
        m_signalLight->red();
    }
}




CreateVehicleDialog::CreateVehicleDialog(VehicleManager* manager, QWidget* parent) : QDialog(parent)
{
    this->setWindowTitle("Fahrzeug hinzufügen");

    m_mainLayout = new QVBoxLayout(this);
    m_info1 = new QLabel("Bitte geben Sie den Fahrzeugnamen\nund die TARA ein.");
    m_mainLayout->addWidget(m_info1);

    m_firstRow = new QHBoxLayout;
    m_name = new QLineEdit;
    m_tara = new QSpinBox;
    m_tara->setMaximum(99999);
    m_firstRow->addWidget(m_name);
    m_firstRow->addWidget(m_tara);
    m_mainLayout->addLayout(m_firstRow);

    m_info2 = new QLabel("\nund wählen Sie die Anzahl der Achsen.");
    m_mainLayout->addWidget(m_info2);

    m_secondRow = new QHBoxLayout;
    m_numberOfAxis = new QSlider;
    m_numberOfAxis->setMinimum(1);
    m_numberOfAxis->setMaximum(5);
    m_numberOfAxis->setOrientation(Qt::Horizontal);
    m_numberOfAxis->setFixedWidth(100);
    m_secondRow->addWidget(m_numberOfAxis);
    m_mainLayout->addLayout(m_secondRow);

    m_thirdRow = new QHBoxLayout;
    for (int i = 0; i < 5; i++)
    {
        QLabel* tmp = new QLabel;
        tmp->setPixmap(QPixmap("./picture/achse.png"));
        tmp->setVisible(false);
        m_axis.push_back(tmp);
        m_thirdRow->addWidget(tmp);
    }
    m_mainLayout->addLayout(m_thirdRow);
    this->updateAxis(1);

    QFrame* frame = new QFrame;
    frame->setFrameShape(QFrame::HLine);
    m_mainLayout->addWidget(frame);
    m_mainLayout->addStretch();

    m_fourthRow = new QHBoxLayout;
    m_accept = new QPushButton("OK");
    m_abort = new QPushButton("Abbruch");
    m_fourthRow->addWidget(m_accept);
    m_fourthRow->addWidget(m_abort);
    m_mainLayout->addLayout(m_fourthRow);

    m_manager = manager;

    connect(m_numberOfAxis, SIGNAL(valueChanged(int)), this, SLOT(updateAxis(int)));
    connect(m_accept, SIGNAL(clicked()), this, SLOT(createVehicle()));
    connect(m_abort, SIGNAL(clicked()), this, SLOT(reject()));
}

void CreateVehicleDialog::updateAxis(int value)
{
    for (int i = 0; i < m_axis.size(); i++)
    {
        if (i < value)
        {
            m_axis.at(i)->setVisible(true);
        }
        else
        {
            m_axis.at(i)->setVisible(false);
        }
    }
}

void CreateVehicleDialog::createVehicle(void)
{
    Vehicle* vehicle = new Vehicle();

    vehicle->setName(m_name->text());
    vehicle->setTara(m_tara->value());
    vehicle->setNumberOfAxis(m_numberOfAxis->value());
    vehicle->setButton(new QPushButton(m_name->text()));

    m_manager->addVehicle(vehicle);
    this->accept();
}





DeleteVehicleDialog::DeleteVehicleDialog(VehicleManager* manager, QWidget* parent) : QDialog(parent)
{
    this->setWindowTitle("Lösche Fahrzeug");
    m_manager = manager;

    m_mainLayout = new QVBoxLayout(this);
    m_list = new QListWidget;
    m_mainLayout->addWidget(m_list);

    m_buttonLayout = new QHBoxLayout;
    m_delete = new QPushButton("Lösche");
    m_close = new QPushButton("Schließen");
    m_buttonLayout->addWidget(m_delete);
    m_buttonLayout->addWidget(m_close);
    m_mainLayout->addLayout(m_buttonLayout);

    this->updateList();

    connect(m_delete, SIGNAL(clicked()), this, SLOT(deleteVehicle()));
    connect(m_close, SIGNAL(clicked()), this, SLOT(accept()));
}

void DeleteVehicleDialog::deleteVehicle(void)
{
    if (m_list->currentRow() >= 0 && m_list->currentRow() < m_list->count())
    {
        m_manager->removeVehicle(m_manager->vehicles().at(m_list->currentRow()));
    }

    this->updateList();
}

void DeleteVehicleDialog::updateList(void)
{
    m_list->clear();

    for (int i = 0; i < m_manager->vehicles().size(); i++)
    {

        m_list->addItem(m_manager->vehicles().at(i)->name());
    }
}


ProductsAndSuppliers::ProductsAndSuppliers(QWidget* parent) : QGroupBox("Wiegeschein", parent)
{
    m_mainLayout = new QGridLayout(this);
    this->setCheckable(true);

    m_products = new QComboBox;
    m_products->setFont(QFont("system", 20, QFont::Normal));
    m_products->setIconSize(QSize(32, 32));
    this->loadProductsFromFile();
    m_mainLayout->addWidget(m_products, 1, 0);

    m_suppliers = new QComboBox;
    m_suppliers->setFont(QFont("system", 20, QFont::Normal));
    this->loadSuppliersFromFile();
    m_suppliers->setIconSize(QSize(32, 32));
    m_mainLayout->addWidget(m_suppliers, 1, 1);

    m_infoProduct = new QLabel("\nWare:");
    m_infoProduct->setFont(QFont("system", 10, QFont::Bold));
    m_mainLayout->addWidget(m_infoProduct, 0, 0);

    m_infoSupplier = new QLabel("\nLieferant:");
    m_infoSupplier->setFont(QFont("system", 10, QFont::Bold));
    m_mainLayout->addWidget(m_infoSupplier, 0, 1);

    m_editProduct = new QPushButton("editieren");
    m_mainLayout->addWidget(m_editProduct, 2, 0);

    m_editSupplier = new QPushButton("editieren");
    m_mainLayout->addWidget(m_editSupplier, 2, 1);

    this->connect(m_editSupplier, SIGNAL(clicked()), this, SLOT(editSupplier()));
    this->connect(m_editProduct, SIGNAL(clicked()), this, SLOT(editProducts()));
}

void ProductsAndSuppliers::loadProductsFromFile(void)
{
    QFile file("products");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Kann die Datei " << file.fileName() << " nicht öffnen.";
        return;
    }

    QTextStream in(&file);
    m_products->clear();

    while (!in.atEnd())
    {
        QString line(in.readLine());
        QStringList list(line.split(":"));
        m_products->insertItem(0, list.at(0));
        m_products->setItemIcon(0, QIcon(QString("picture/").append(list.at(1))));
    }
}

void ProductsAndSuppliers::loadSuppliersFromFile(void)
{
    QFile file("suppliers");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Kann die Datei " << file.fileName() << " nicht öffnen.";
        return;
    }

    QTextStream in(&file);
    m_suppliers->clear();

    while (!in.atEnd())
    {
        QString line(in.readLine());
        QStringList list(line.split(":"));
        m_suppliers->insertItem(0, list.at(0));
        m_suppliers->setItemIcon(0, QIcon(QString("picture/").append(list.at(1))));
    }
}

void ProductsAndSuppliers::editSupplier(void)
{
    SupplierDialog dialog("suppliers");

    dialog.exec();
    this->loadSuppliersFromFile();
}

void ProductsAndSuppliers::editProducts(void)
{
    ProductDialog dialog("products");

    dialog.exec();
    this->loadProductsFromFile();
}
