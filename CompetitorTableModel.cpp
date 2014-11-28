#include "CompetitorTableModel.h"
#include "JudoMasterApplication.h"

CompetitorTableModel::CompetitorTableModel(QObject *parent) :
    QAbstractTableModel(parent)
    , m_clubId(-1)
{
    connect(JMApp()->competitorController(), &CompetitorController::competitorAdded, this, &CompetitorTableModel::addCompetitor);
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
        case Qt::DisplayRole:
            switch(index.column())
            {
                case 0:
                    return QVariant(judoka->firstName());
                break;

                case 1:
                    return QVariant(judoka->lastName());
                break;

                case 2:
                    return QVariant(judoka->gender());
                break;

                case 3:
                    return QVariant(judoka->age());
                break;

                case 4:
                    return QVariant(judoka->weight());
                break;

                case 5:
                    switch(judoka->rank())
                    {
                        case White:
                            return QVariant("White");
                        break;
                        case Yellow:
                            return QVariant("Yellow");
                            break;
                        case Orange:
                            return QVariant("Orange");
                            break;
                        case Green:
                            return QVariant("Green");
                            break;
                        case Blue:
                            return QVariant("Blue");
                            break;
                        case Purple:
                            return QVariant("Purple");
                            break;
                        case Brown:
                            return QVariant("Brown");
                            break;
                        case Black:
                            return QVariant("Black");
                            break;

                        default:
                            return QVariant("Unknown");
                    }

                break;

            }

        break;
    }

    return QVariant();
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
