#include "ClubsEditor.h"
#include "ui_ClubsEditor.h"

#include "JudoMasterApplication.h"
#include <QAbstractListModel>


class ClubModel : public QAbstractListModel
{
public:
    ClubModel(QObject* parent = 0) :
        QAbstractListModel(parent)
    {

    }

    QModelIndex addClub(Club* club)
    {
        ClubController *controller = JMApp()->clubController();
        beginInsertRows(QModelIndex(), controller->clubs()->size(), controller->clubs()->size() + 1);
        controller->addClub(*club);
        endInsertRows();

        return createIndex(controller->clubs()->size() - 1, 0);
    }

    Club* club(const QModelIndex &index)
    {
        Club *c = JMApp()->clubController()->clubs()->at(index.row());
        return c;
    }

    int rowCount(const QModelIndex &parent) const
    {
        if(JMApp()->clubController()->isValid())
            return (JMApp()->clubController()->clubs()->size());
        return 0;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        Club *club = JMApp()->clubController()->clubs()->at(index.row());

        switch(role)
        {
            case Qt::DisplayRole:
                return QVariant(club->clubName());
            break;

            default:
                return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        switch(role)
        {
            case Qt::DisplayRole:
                return QVariant(QString("Club Name"));
        }
    }

    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    int findNextClubId()
    {
        int nextId = 0;
        foreach (Club* club, *JMApp()->clubController()->clubs())
        {

            nextId = std::max(nextId, club->id());
        }

        // We now have the max club id.
        nextId++;

        return nextId;
    }

};



ClubsEditor::ClubsEditor(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::ClubsEditor)
{
    ui->setupUi(this);

    ui->clubList->setModel(new ClubModel(ui->clubList));

    connect(ui->addClubBtn, &QPushButton::clicked, this, &ClubsEditor::addClub);
    connect(this, &ClubsEditor::clubAdded, ui->clubEditor, &ClubEditor::editClub);
    connect(ui->clubList, &QListView::clicked, this, &ClubsEditor::clubSelected);
    connect(this, &ClubsEditor::clubSelect, ui->clubEditor, &ClubEditor::editClub);

}

ClubsEditor::~ClubsEditor()
{
    delete ui;
}

void ClubsEditor::setClubs(QList<Club *> *clubs)
{

    // DELETE
}

void ClubsEditor::addClub()
{
    ClubModel* model = dynamic_cast<ClubModel *>(ui->clubList->model());
    if(!model)
        return; // Handle null value


    Club* nclub = new Club(model->findNextClubId(), "<New Club>", "<Coach Name>", "", "", "USA", "", "WA", "");
    QModelIndex addedIndex = model->addClub(nclub);

    ui->clubList->selectionModel()->select(addedIndex, QItemSelectionModel::ClearAndSelect);
    emit clubAdded(nclub);
}

void ClubsEditor::clubSelected(const QModelIndex &index)
{
    ClubModel* model = dynamic_cast<ClubModel *>(ui->clubList->model());
    if(!model)
        return; // Handle null value

    emit clubSelect(model->club(index));
}
