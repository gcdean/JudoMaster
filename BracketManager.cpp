#include "BracketManager.h"
#include "ui_BracketManager.h"

#include "Bracket.h"
#include "BracketCompetitorTableModel.h"
#include "BracketEditor.h"
#include "BracketTableModel.h"
#include "BracketTypeItemDelegate.h"
#include "Competitor.h"
#include "CompetitorFilter.h"
#include "CompetitorTableModel.h"
#include "JMUtil.h"
#include "JudoMasterApplication.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QList>
#include <QSortFilterProxyModel>
#include <QStyledItemDelegate>
#include <QTableView>



BracketManager::BracketManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BracketManager)
    , m_currentBracket(0)
{
    ui->setupUi(this);

    m_bracketItemDelegate = new BracketTypeItemDelegate();
    ui->bracketList->setTableItemDelegate(m_bracketItemDelegate);
    m_bracketModel = new BracketTableModel(this);
    ui->bracketList->setModel(m_bracketModel);
    ui->bracketList->setController(JMApp()->bracketController());
    ui->bracketList->tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bracketList->tableView()->verticalHeader()->setVisible(true);
    ui->bracketList->tableView()->setSortingEnabled(false);


    ui->allCompetitors->tableView()->setSortingEnabled(true);
    ui->allCompetitors->setDisplayEditButtons(false);
    ui->allCompetitors->tableView()->setDragEnabled(true);
    ui->allCompetitors->tableView()->setDragDropMode(QAbstractItemView::DragOnly);
    ui->allCompetitors->tableView()->setDropIndicatorShown(true);
    ui->allCompetitors->tableView()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->allCompetitors->tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->allCompetitors->tableView()->verticalHeader()->setVisible(true);

    ui->bracketCompetitors->setDisplayEditButtons(false);
    m_bracketCompetitorModel = new BracketCompetitorTableModel(JMApp()->bracketController());
    ui->bracketCompetitors->setModel(m_bracketCompetitorModel);
    ui->bracketCompetitors->tableView()->setDragDropMode(QAbstractItemView::DragDrop);
    ui->bracketCompetitors->tableView()->setAcceptDrops(true);
    ui->bracketCompetitors->tableView()->viewport()->setAcceptDrops(true);
    ui->bracketCompetitors->tableView()->setDropIndicatorShown(true);
    ui->bracketCompetitors->tableView()->setSortingEnabled(false);
    ui->bracketCompetitors->tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->bracketList->tableView()->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &BracketManager::rowChanged);
    connect(ui->allCompetitorsFilter, &CompetitorFilterWidget::applyFilter, this, &BracketManager::competitorFilterChanged);
    connect(JMApp()->bracketController(), &ClubController::tournamentChanged, this, &BracketManager::tournamentChanged);
    connect(ui->removeBtn, &QPushButton::clicked, this, &BracketManager::removeCompetitorFromBracket);
    connect(ui->allCompetitors->tableView()->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, &BracketManager::viewCompetitor);
    connect(ui->bracketList->tableView()->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, &BracketManager::editBracket);
    connect(m_bracketCompetitorModel, &BracketCompetitorTableModel::numCompetitorsChanged, this, &BracketManager::resetMatCompetitors);
    connect(m_bracketItemDelegate, &BracketTypeItemDelegate::matNumberChanged, this, &BracketManager::resetMatCompetitors);

}

BracketManager::~BracketManager()
{
    delete ui;
    delete m_bracketModel;
}

void BracketManager::resetMatCompetitors()
{
    int mat1 = 0;
    int mat2 = 0;

    const QList<Bracket *> *brackets = JMApp()->bracketController()->brackets();
    foreach(Bracket *bracket, *brackets)
    {
        if(bracket->matNumber() == 1)
            mat1 += bracket->competitors().size();
        if(bracket->matNumber() == 2)
            mat2 += bracket->competitors().size();
    }

    ui->mat1Cntr->display(mat1);
    ui->ma2Cntr->display(mat2);
}

void BracketManager::addBracket()
{
    qDebug() << "ADD A BRACKET";
}

void BracketManager::tournamentChanged()
{
    ui->bracketList->setModel(new BracketTableModel());
    connect(ui->bracketList->tableView()->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &BracketManager::rowChanged);
    ui->bracketList->tableView()->resizeColumnsToContents();

    CompetitorTableModel *allCompTableModel = new CompetitorTableModel(JMApp()->competitorController(), this);
    allCompTableModel->setParentId(-1);
    allCompTableModel->setEditable(false);

    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(allCompTableModel);

    ui->allCompetitors->tableView()->setModel(proxyModel);
    ui->allCompetitors->tableView()->resizeColumnsToContents();

    resetMatCompetitors();
}

void BracketManager::rowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.row() == previous.row())
    {
        return;
    }

    BracketTableModel* model = dynamic_cast<BracketTableModel *>(ui->bracketList->tableModel());
    if(model)
    {
        // Get the index of the selected item.
        // Get the bracket id of the selected item.
        QVariant qv = model->data(current, Qt::UserRole);

        // Set the id in the competitor list.
        if(qv.isValid())
        {
            m_currentBracket = dynamic_cast<Bracket *>(JMApp()->bracketController()->find(qv.toInt()));
            CompetitorTableModel* cmodel = dynamic_cast<CompetitorTableModel *>(ui->bracketCompetitors->tableModel());
            cmodel->setParentId(qv.toInt());
        }
    }

}

void BracketManager::competitorFilterChanged(const CompetitorFilter &filter)
{
    qDebug() << "BracketManager::competitorFilterChanged() minAge: " << filter.minAge() << ", maxAge: " << filter.maxAge() << ", minWeight: " << filter.minWeight() << ", maxWeight: " << filter.maxWeight();

    QSortFilterProxyModel* proxyModel = dynamic_cast<QSortFilterProxyModel *>(ui->allCompetitors->tableView()->model());
    CompetitorTableModel* cmodel = dynamic_cast<CompetitorTableModel *>(proxyModel->sourceModel());
    cmodel->setFilter(filter);

}

void BracketManager::removeCompetitorFromBracket()
{
    if(!m_currentBracket)
        return;

    QModelIndexList lst = ui->bracketCompetitors->tableView()->selectionModel()->selectedRows();
    foreach(const QModelIndex& index, lst)
    {
        Competitor *competitor = m_currentBracket->competitors().at(index.row());
        JMApp()->bracketController()->removeCompetitorFromBracket(m_currentBracket->id(), competitor->id());
    }

    resetMatCompetitors();

}

void BracketManager::viewCompetitor(int logicalIndex)
{
    qDebug() << "BracketManager::viewCompetitor() - index: " << logicalIndex;
    QAbstractItemModel *model = ui->allCompetitors->tableView()->model();
    QModelIndex index = model->index(logicalIndex, 0);
    QVariant qv = model->data(index);
    if(qv.isValid())
    {
        qDebug() << "    Text is: " << qv.toString();
    }
    else
    {
        qDebug() << "    UNKNOWN";
    }
}

void BracketManager::editBracket(int logicalIndex)
{
    qDebug() << "BracketManager::editBracket(" << logicalIndex << ")";
    QModelIndex modelIndex = m_bracketModel->index(logicalIndex, 0);
    QVariant qv = m_bracketModel->data(modelIndex, Qt::UserRole);
    Bracket *bracket = dynamic_cast<Bracket *>(JMApp()->bracketController()->find(qv.toInt()));

    BracketEditor be(bracket, this);
    be.exec();
}
