#include "ClubsEditor.h"
#include "ui_ClubsEditor.h"

#include <QAbstractListModel>


class ClubModel : public QAbstractListModel
{
public:
    ClubModel(QList<Club *>* clubs, QObject* parent = 0) :
        QAbstractListModel(parent)
    {
        m_clubs = clubs;
    }

    QModelIndex addClub(Club* club)
    {
        beginInsertRows(QModelIndex(), m_clubs->size(), m_clubs->size() + 1);
        m_clubs->append(club);
        endInsertRows();

        return createIndex(m_clubs->size() - 1, 0);
    }

    Club* club(const QModelIndex &index)
    {
        Club *c = m_clubs->at(index.row());
        return c;
    }

    int rowCount(const QModelIndex &parent) const
    {
        if(m_clubs)
            return m_clubs->size();
        else
            return 0;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        Club *club = m_clubs->at(index.row());

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
        foreach (Club* club, *m_clubs)
        {

            nextId = std::max(nextId, club->id());
        }

        // We now have the max club id.
        nextId++;

        return nextId;
    }

private:
    QList<Club *>* m_clubs;
};



ClubsEditor::ClubsEditor(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::ClubsEditor)
    , m_clubs(0)
{
    ui->setupUi(this);
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
    if(m_clubs && m_clubs->size() > 0)
    {
        // Clear the list.
    }

    if(!clubs)
    {
        return; // Cleaning out the list
    }
    m_clubs = clubs;

    ui->clubList->setModel(new ClubModel(m_clubs, ui->clubList));

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

    Club *club = model->club(index);
    emit clubSelect(model->club(index));
}
