#ifndef ___SUPPLIER_DIALOG_H___
#define ___SUPPLIER_DIALOG_H___

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QFile>

class SupplierDialog : public QDialog
{
    Q_OBJECT

public:
    SupplierDialog(const QString& file, QWidget* parent = 0);

private slots:
    void insertSupplier(void);
    void removeSupplier(void);

private:
    void readCompleteFile(void);

    QFile        m_file;
    QVBoxLayout* m_mainLayout;
    QGridLayout* m_createLayout;
    QGridLayout* m_deleteLayout;
    QGroupBox*   m_groupCreate;
    QGroupBox*   m_groupDelete;
    QPushButton* m_deleteButton;
    QPushButton* m_closeButton;
    QPushButton* m_createButton;
    QListWidget* m_list;
    QLineEdit*   m_line;
};

#endif
