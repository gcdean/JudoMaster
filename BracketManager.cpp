#include "BracketManager.h"
#include "ui_BracketManager.h"

#include "Bracket.h"
#include "BracketCompetitorTableModel.h"
#include "BracketTableModel.h"
#include "Competitor.h"
#include "CompetitorFilter.h"
#include "CompetitorTableModel.h"
#include "JMUtil.h"
#include "JudoMasterApplication.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QStyledItemDelegate>
#include <QTableView>


class BracketTypeItemDelegate : public QStyledItemDelegate
{
public:
    BracketTypeItemDelegate(QObject* parent = 0) : QStyledItemDelegate(parent) {}

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QWidget *widget = 0;
        switch(index.column())
        {
            case bracket::Gender:
            case bracket::Type:
                widget =  new QComboBox(parent);
                break;

            default:
               widget = QStyledItemDelegate::createEditor(parent, option, index);
        }


        return widget;
    }

    void setEditorData(QWidget * editor, const QModelIndex & index) const
    {
        switch(index.column())
        {
            case bracket::Gender:
            {
                QComboBox *combo = dynamic_cast<QComboBox *>(editor);
                if(combo)
                {
                    combo->addItem("Male");
                    combo->addItem("Female");

                    // Need to select the right one.
                    QVariant var = index.model()->data(index);
                    if(genderFromString(var.toString()) == JM::Male)
                        combo->setCurrentIndex(0);
                    else
                        combo->setCurrentIndex(1);
                }
                break;
            }
            case bracket::Type:
            {
                QComboBox *combo = dynamic_cast<QComboBox *>(editor);
                if(combo)
                {
                    combo->addItem("Light");
                    combo->addItem("Medium");
                    combo->addItem("Heavy");
                    combo->addItem("Super Heavy");
                    combo->addItem("IFJ");

                    // Need to select the right one.
                    QVariant var = index.model()->data(index);
                    combo->setCurrentIndex(bracket::weightTypeFromStr(var.toString()));
                }
                break;
            }

            default:
                QStyledItemDelegate::setEditorData(editor, index);
        }
    }

    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
    {
        switch(index.column())
        {
            case bracket::Gender:
            {
                QComboBox *combo = dynamic_cast<QComboBox *>(editor);
                if(combo)
                {
                    model->setData(index, QVariant(combo->currentText()));
                }
                break;
            }
            case bracket::Type:
            {
                QComboBox *combo = dynamic_cast<QComboBox *>(editor);
                if(combo)
                {
                    int idx = combo->currentIndex();
                    model->setData(index, QVariant(combo->currentIndex()));
                }
                break;
            }

            default:
                QStyledItemDelegate::setModelData(editor, model, index);
        }
    }
};

BracketManager::BracketManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BracketManager)
    , m_currentBracket(0)
{
    ui->setupUi(this);

    ui->bracketList->setTableItemDelegate(new BracketTypeItemDelegate());
    ui->bracketList->setModel(new BracketTableModel());
    ui->bracketList->setController(JMApp()->bracketController());
    ui->bracketList->tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bracketList->tableView()->verticalHeader()->setVisible(true);


    ui->allCompetitors->tableView()->setSortingEnabled(true);
    ui->allCompetitors->setDisplayEditButtons(false);
    ui->allCompetitors->tableView()->setDragEnabled(true);
    ui->allCompetitors->tableView()->setDragDropMode(QAbstractItemView::DragOnly);
    ui->allCompetitors->tableView()->setDropIndicatorShown(true);
    ui->allCompetitors->tableView()->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->allCompetitors->tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->allCompetitors->tableView()->verticalHeader()->setVisible(true);

    ui->bracketCompetitors->setDisplayEditButtons(false);
    ui->bracketCompetitors->setModel(new BracketCompetitorTableModel(JMApp()->bracketController()));
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
}

BracketManager::~BracketManager()
{
    delete ui;
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
