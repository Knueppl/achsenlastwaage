#include "SupplierDialog.h"

#include <QDebug>

SupplierDialog::SupplierDialog(const QString& file, QWidget* parent)
    : QDialog(parent),
      m_file(file)
{
    m_mainLayout = new QVBoxLayout(this);

    m_groupCreate = new QGroupBox("hinzufügen");
    m_createLayout = new QGridLayout;
    m_line = new QLineEdit;
    m_createButton = new QPushButton("hinzufügen");
    m_createLayout->addWidget(m_line, 0, 0);
    m_createLayout->addWidget(m_createButton, 0, 1);
    m_groupCreate->setLayout(m_createLayout);
    m_mainLayout->addWidget(m_groupCreate);

    m_groupDelete = new QGroupBox("löschen");
    m_deleteLayout = new QGridLayout;
    m_list = new QListWidget;
    m_deleteButton = new QPushButton("löschen");
    m_deleteLayout->addWidget(m_list, 0, 0);
    m_deleteLayout->addWidget(m_deleteButton, 0, 1);
    m_groupDelete->setLayout(m_deleteLayout);
    m_mainLayout->addWidget(m_groupDelete);

    m_closeButton = new QPushButton("schließen");
    m_closeButton->setDefault(true);
    m_mainLayout->addWidget(m_closeButton);

    if (!m_file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Kann die Datei " << m_file.fileName() << " nicht öffnen.";
        this->reject();
        return;
    }

    this->readCompleteFile();

    this->connect(m_closeButton, SIGNAL(clicked()), this, SLOT(accept()));
    this->connect(m_createButton, SIGNAL(clicked()), this, SLOT(insertSupplier()));
}

void SupplierDialog::readCompleteFile(void)
{
    QTextStream in(&m_file);

    while (!in.atEnd())
    {
        QString line(in.readLine());
        QStringList list(line.split(":"));
        m_list->insertItem(0, list.at(0));
    }
}

void SupplierDialog::insertSupplier(void)
{
    QTextStream out(&m_file);

    out << m_line->text() << ":\n";
    m_file.flush();
    this->readCompleteFile();
}

void SupplierDialog::removeSupplier(void)
{

}
