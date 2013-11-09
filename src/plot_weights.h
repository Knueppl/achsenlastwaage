#ifndef _PLOT_WEIGHTS_H_
#define _PLOT_WEIGHTS_H_

#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QString>
#include <QList>
#include <QToolBox>
#include <QTreeWidget>
#include <QTableWidget>

#include "weight_list.h"

class OrderedBySupplier : public QToolBox
{
public:
    OrderedBySupplier(QWidget* parent = 0);

    void addWeight(const Weight* weight);

private:
    void addChild(QTreeWidgetItem* top, const Weight* weight);
    void calcSumTree(QTreeWidgetItem* top);
    void calcSumTable(void);

    QTreeWidget*  m_tree;
    QTableWidget* m_table;
};

class PlotWeights : public QWidget
{
    Q_OBJECT;

public:
    PlotWeights(const QString& directory = "", QWidget* parent = 0);
    ~PlotWeights(void);

public slots:
    void getWeights(void);
    void saveAllToFile(void);

private slots:
    void sortWeights(void);

private:
    QHBoxLayout*   m_mainLayout;
    QVBoxLayout*   m_controlLayout;
    QTabWidget*    m_tabs;
    QDir*          m_directory;
    QList<Weight*> m_weights;
};

#endif
