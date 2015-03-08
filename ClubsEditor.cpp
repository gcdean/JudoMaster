#include "ClubsEditor.h"
#include "ui_ClubsEditor.h"

#include "ClubListModel.h"
#include "CompetitorItemDelegate.h"
#include "CompetitorTableModel.h"
#include "JudoMasterApplication.h"

#include <QAbstractListModel>

#include <QDebug>
#include <QSortFilterProxyModel>
#include <QTableView>

ClubsEditor::ClubsEditor(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::ClubsEditor)
{
    ui->setupUi(this);

    ui->clubList->setModel(new ClubListModel(ui->clubList));

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
