#include "CompetitorTableModel.h"
#include "JudoMasterApplication.h"
#include "JMUtil.h"

#include <QColor>

CompetitorTableModel::CompetitorTableModel(QObject *parent) :
    QAbstractTableModel(parent)
    , m_clubId(-1)
{
    connect(JMApp()->competitorController(), &CompetitorController::competitorAdded, this, &CompetitorTableModel::addCompetitor);
}

void CompetitorTableModel::setClubId(int id)
{
    beginResetModel();
    m_clubId = id;
    endResetModel();
}

int CompetitorTableModel::rowCount(const QModelIndex &) const
{
    if(m_clubId != -1)
        return JMApp()->competitorController()->numClubCompetitors(m_clubId);
    else
        return JMApp()->competitorController()->competitors().size();
}

int CompetitorTableModel::columnCount(const QModelIndex &) const
{
    return 6;
}

QVariant CompetitorTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch(section)
        {
            case 0:
                return QVariant("First");
            break;

            case 1:
                return QVariant("Last");
            break;

            case 2:
                return QVariant("Gender");
            break;

            case 3:
                return QVariant("Age");
            break;

            case 4:
                return QVariant("Weight");
            break;

            case 5:
                return QVariant("Rank");
            break;

        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant CompetitorTableModel::data(const QModelIndex &index, int role) const
{
    // Get the competitor.
    const QList<Competitor *> competitors = JMApp()->competitorController()->competitors(m_clubId);
    const Competitor *judoka = competitors.at(index.row());
    switch(role)
    {
        case Qt::BackgroundRole:
            if(index.column() == 5)
            {
                return QVariant(rankToColor(judoka->rank()));
            }

        break;

        case Qt::DisplayRole:
        case Qt::EditRole:
            switch(index.column())
            {
                case 0:
                    return QVariant(judoka->firstName());
                break;

                case 1:
                    return QVariant(judoka->lastName());
                break;

                case 2:
                    return QVariant(genderToString(judoka->gender()));
                break;

                case 3:
                    return QVariant(judoka->age());
                break;

                case 4:
                    return QVariant(judoka->weight());
                break;

                case 5:
                    return QVariant(rankToString(judoka->rank()));

                break;

            }

        break;
    }

    return QVariant();
}

Qt::ItemFlags CompetitorTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    int col = index.column();
    if(col == 0 || col == 1)
    {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

bool CompetitorTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool updated = false;
    const QList<Competitor *> competitors = JMApp()->competitorController()->competitors(m_clubId);
    Competitor *competitor = competitors.at(index.row());

    switch(index.column())
    {
        case 0: // First Name
            competitor->setFirstName(value.toString());
            updated = true;
        break;

        case 1: // Last Name
            competitor->setLastName(value.toString());
            updated = true;
        break;
    }

    if(updated)
    {
        emit dataChanged(index, index);
    }
    return updated;

}

void CompetitorTableModel::addCompetitor(Competitor *competitor)
{
   if(m_clubId == -1 || m_clubId == competitor->clubId())
   {
       int numCompetitors = JMApp()->competitorController()->numClubCompetitors(m_clubId) - 1;
       beginInsertRows(QModelIndex(), numCompetitors, numCompetitors);
       endInsertRows();
   }
}
