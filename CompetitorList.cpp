#include "CompetitorList.h"
#include "ui_CompetitorList.h"

#include "ClubController.h"
#include "CompetitorTableModel.h"
#include "JudoMasterApplication.h"

#include <QAbstractItemDelegate>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>
#include <QTableView>

#include <QDebug>

CompetitorList::CompetitorList(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::CompetitorList)
    , m_clubId(-1)
    , m_controller(0)
{
    ui->setupUi(this);

    connect(ui->addBtn, &QPushButton::clicked, this, &CompetitorList::add);
    connect(ui->deleteBtn, &QPushButton::clicked, this, &CompetitorList::remove);
    connect(JMApp()->clubController(), &ClubController::tournamentChanged, this, &CompetitorList::tournamentChanged);
}

CompetitorList::~CompetitorList()
{
    delete ui;
}

void CompetitorList::setClubId(int id)
{
    m_clubId = id;
    CompetitorTableModel *model = dynamic_cast<CompetitorTableModel *>(ui->competitorTable->model());

    if(!model)
    {
        QSortFilterProxyModel* proxyModel = dynamic_cast<QSortFilterProxyModel *>(ui->competitorTable->model());
        if(proxyModel)
        {
            model = dynamic_cast<CompetitorTableModel*>(proxyModel->sourceModel());
        }
    }
    if(model)
    {
        model->setParentId(id);
    }
    ui->competitorTable->reset();
}

QAbstractTableModel* CompetitorList::tableModel()
{
    return dynamic_cast<QAbstractTableModel *>(ui->competitorTable->model());
}

QTableView* CompetitorList::tableView()
{
    return ui->competitorTable;
}

void CompetitorList::setModel(QAbstractTableModel *model)
{
    model->setParent(ui->competitorTable);
    ui->competitorTable->setModel(model);
}

void CompetitorList::setTableItemDelegate(QAbstractItemDelegate *delegate)
{
    ui->competitorTable->setItemDelegate(delegate);
}

bool CompetitorList::displayEditButtons()
{
    return ui->editButtons->isVisible();
}

void CompetitorList::setDisplayEditButtons(bool display)
{
    ui->editButtons->setVisible(display);
}

void CompetitorList::setController(BaseController *controller)
{
    m_controller = controller;
}

void CompetitorList::add()
{
    if(m_controller)
    {
        m_controller->add(m_clubId);
    }
}

void CompetitorList::remove()
{
    // Remove Selected items.
    if(m_controller)
    {
        QModelIndexList lst = ui->competitorTable->selectionModel()->selectedRows();
        foreach(const QModelIndex& index, lst)
        {
            qDebug() << "CompetitorList::remove() - Row: " << index.row();
            m_controller->removeIndex(index.row());
        }

    }
}

void CompetitorList::tournamentChanged()
{
    ui->competitorTable->reset();
}
