#include "BracketManager.h"
#include "ui_BracketManager.h"

#include "BracketTableModel.h"
#include "CompetitorFilter.h"
#include "CompetitorTableModel.h"
#include "JMUtil.h"
#include "JudoMasterApplication.h"

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
                    combo->addItem("IFJ");
                    combo->addItem("Light/Medium/Heavy");

                    // Need to select the right one.
                    QVariant var = index.model()->data(index);
                    if(var.toString() == "IJF")
                        combo->setCurrentIndex(0);
                    else
                        combo->setCurrentIndex(1);
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
{
    ui->setupUi(this);

    ui->bracketList->setTableItemDelegate(new BracketTypeItemDelegate());
    ui->bracketList->setModel(new BracketTableModel());
    ui->bracketList->setController(JMApp()->bracketController());

    ui->allCompetitors->tableView()->setSortingEnabled(true);
    ui->allCompetitors->setDisplayEditButtons(false);
    ui->allCompetitors->tableView()->setDragEnabled(true);
    ui->allCompetitors->tableView()->setDragDropMode(QAbstractItemView::DragOnly);
    ui->allCompetitors->tableView()->setDropIndicatorShown(true);
    ui->allCompetitors->tableView()->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->bracketCompetitors->setDisplayEditButtons(false);
    ui->bracketCompetitors->setModel(new CompetitorTableModel(JMApp()->bracketController()));
    //ui->bracketCompetitors->tableView()->setDragDropMode(QAbstractItemView::DropOnly);
    ui->bracketCompetitors->tableView()->setAcceptDrops(true);
    ui->bracketCompetitors->tableView()->viewport()->setAcceptDrops(true);
    ui->bracketCompetitors->tableView()->setDropIndicatorShown(true);

    connect(ui->bracketList->tableView()->selectionModel(), &QItemSelectionModel::currentChanged, this, &BracketManager::bracketChanged);
    connect(ui->bracketList->tableView()->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &BracketManager::rowChanged);

    connect(ui->allCompetitorsFilter, &CompetitorFilterWidget::applyFilter, this, &BracketManager::competitorFilterChanged);
    connect(JMApp()->bracketController(), &ClubController::tournamentChanged, this, &BracketManager::tournamentChanged);

}

BracketManager::~BracketManager()
{
    delete ui;
}

void BracketManager::addBracket()
{
    qDebug() << "ADD A BRACKET";
}

void BracketManager::bracketChanged(const QModelIndex &current, const QModelIndex &previous)
{
    qDebug() << "BracketManager::bracketChanged() - start";
    if(current.row() == previous.row())
    {
        qDebug() << "    Row has not changed. Do Nothing.";
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
            CompetitorTableModel* cmodel = dynamic_cast<CompetitorTableModel *>(ui->bracketCompetitors->tableModel());
            qDebug() << "    Setting id in bracket competitors to: " << qv.toInt();
            cmodel->setParentId(qv.toInt());
        }
    }
    qDebug() << "BracketManager::bracketChanged() - end";
}

void BracketManager::tournamentChanged()
{
    qDebug() << "BracketManager::tournamentChanged()";
    ui->bracketList->setModel(new BracketTableModel());
    connect(ui->bracketList->tableView()->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &BracketManager::rowChanged);

    CompetitorTableModel *allCompTableModel = new CompetitorTableModel(JMApp()->competitorController(), this);
    allCompTableModel->setParentId(-1);
    allCompTableModel->setEditable(false);

    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(allCompTableModel);

    ui->allCompetitors->tableView()->setModel(proxyModel);
}

void BracketManager::rowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    qDebug() << "BracketManager::rowChanged() - start";
    if(current.row() == previous.row())
    {
        qDebug() << "    Row has not changed. Do Nothing.";
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
            CompetitorTableModel* cmodel = dynamic_cast<CompetitorTableModel *>(ui->bracketCompetitors->tableModel());
            qDebug() << "    Setting id in bracket competitors to: " << qv.toInt();
            cmodel->setParentId(qv.toInt());
        }
    }
    qDebug() << "BracketManager::rowChanged() - end";

}

void BracketManager::competitorFilterChanged(const CompetitorFilter &filter)
{
    qDebug() << "BracketManager::competitorFilterChanged() minAge: " << filter.minAge() << ", maxAge: " << filter.maxAge() << ", minWeight: " << filter.minWeight() << ", maxWeight: " << filter.maxWeight();

    QSortFilterProxyModel* proxyModel = dynamic_cast<QSortFilterProxyModel *>(ui->allCompetitors->tableView()->model());
    CompetitorTableModel* cmodel = dynamic_cast<CompetitorTableModel *>(proxyModel->sourceModel());
    cmodel->setFilter(filter);

}
