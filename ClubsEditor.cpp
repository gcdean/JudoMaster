#include "ClubsEditor.h"
#include "ui_ClubsEditor.h"

#include "ClubListModel.h"
#include "CompetitorItemDelegate.h"
#include "CompetitorTableModel.h"
#include "JudoMasterApplication.h"
#include "commands/PrintRegistrationCommand.h";

#include <QAbstractListModel>

#include <QDebug>
#include <QMenu>
#include <QSortFilterProxyModel>
#include <QTableView>

ClubsEditor::ClubsEditor(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::ClubsEditor)
    , m_printClubRegAction(0)
{
    ui->setupUi(this);

    m_printClubRegAction = new QAction("Print Registration...", this);

    ui->clubList->setModel(new ClubListModel(ui->clubList));
//    ui->clubList->setDragEnabled(true);
//    ui->clubList->setDragDropMode(QAbstractItemView::InternalMove);
//    ui->clubList->setDropIndicatorShown(true);
//    ui->clubList->setAcceptDrops(true);
//    ui->clubList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->clubList->setContextMenuPolicy(Qt::CustomContextMenu);


    CompetitorTableModel *sourceModel = new CompetitorTableModel(JMApp()->competitorController(), this);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(sourceModel);

    ui->competitorsList->tableView()->setSortingEnabled(true);
    ui->competitorsList->tableView()->setModel(proxyModel);
    ui->competitorsList->setTableItemDelegate(new CompetitorItemDelegate);
    ui->competitorsList->setController(JMApp()->competitorController());

    connect(ui->addClubBtn, &QPushButton::clicked, this, &ClubsEditor::addClub);
    connect(ui->removeClubBtn, &QPushButton::clicked, this, &ClubsEditor::removeClub);
    connect(this, &ClubsEditor::clubAdded, ui->clubEditor, &ClubEditor::editClub);
    connect(this, &ClubsEditor::clubSelect, ui->clubEditor, &ClubEditor::editClub);

    connect(ui->clubList->selectionModel(), &QItemSelectionModel::currentChanged, this, &ClubsEditor::clubSelected);
    connect(JMApp()->clubController(), &ClubController::tournamentChanged, this, &ClubsEditor::tournamentChanged);

    connect(ui->clubList, &QWidget::customContextMenuRequested, this, &ClubsEditor::clubContextMenu);
    connect(m_printClubRegAction, &QAction::triggered, this, &ClubsEditor::printClubRegistration);

}

ClubsEditor::~ClubsEditor()
{
    delete ui;
}

void ClubsEditor::addClub()
{
    ClubListModel* model = dynamic_cast<ClubListModel *>(ui->clubList->model());
    if(!model)
        return; // Handle null value

    JMApp()->clubController()->createClub();
    QModelIndex addedIndex = model->index(JMApp()->clubController()->clubs()->size() - 1, 0);
    ui->clubList->selectionModel()->select(addedIndex, QItemSelectionModel::ClearAndSelect);
    clubSelected(addedIndex);
}

void ClubsEditor::removeClub()
{
    QModelIndexList selected = ui->clubList->selectionModel()->selectedIndexes();
    for(int x = 0; x < selected.size(); x++)
    {
        QModelIndex index = selected[x];
        qDebug() << "Removing Row: " << index.row();
        JMApp()->clubController()->removeIndex(index.row());
    }
}

void ClubsEditor::clubSelected(const QModelIndex &index)
{
    ClubListModel* model = dynamic_cast<ClubListModel *>(ui->clubList->model());
    if(!model)
        return; // Handle null value

    ui->competitorsList->setClubId(model->club(index)->id());
    emit clubSelect(model->club(index));
}

void ClubsEditor::tournamentChanged()
{
    ui->clubList->reset();
}

void ClubsEditor::clubContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->clubList->viewport()->mapToGlobal(pos);

    QMenu contextMenu;
    contextMenu.addAction(m_printClubRegAction);

    contextMenu.exec(globalPos);

}

void ClubsEditor::printClubRegistration()
{
    QModelIndexList indexes = ui->clubList->selectionModel()->selectedRows();
    QList<Club *> selectedClubs;
    foreach(QModelIndex index, indexes)
    {
        Club *club = dynamic_cast<Club *>(JMApp()->clubController()->find(ui->clubList->model()->data(index, Qt::UserRole).toInt()));
        if(club)
        {
            selectedClubs.append(club);
        }
    }

    PrintRegistrationCommand cmd(this, selectedClubs);
    cmd.run();
}
