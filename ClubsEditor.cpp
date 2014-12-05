#include "ClubsEditor.h"
#include "ui_ClubsEditor.h"

#include "ClubListModel.h"
#include "JudoMasterApplication.h"
#include <QAbstractListModel>

#include <QDebug>

ClubsEditor::ClubsEditor(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::ClubsEditor)
{
    ui->setupUi(this);

    ui->clubList->setModel(new ClubListModel(ui->clubList));

    connect(ui->addClubBtn, &QPushButton::clicked, this, &ClubsEditor::addClub);
    connect(this, &ClubsEditor::clubAdded, ui->clubEditor, &ClubEditor::editClub);
    //connect(ui->clubList, &QListView::clicked, this, &ClubsEditor::clubSelected);
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
