#include "CompetitorTableModel.h"

#include "Bracket.h"
#include "Competitor.h"
#include "JudoMasterApplication.h"
#include "JMUtil.h"

#include <QColor>
#include <QDebug>
#include <QHash>
#include <QMimeData>

CompetitorTableModel::CompetitorTableModel(BaseController *controller, QObject *parent) :
    QAbstractTableModel(parent)
    , m_controller(controller)
    , m_parentId(-1)
    , m_editable(true)
{
    connect(JMApp()->competitorController(), &CompetitorController::competitorAdded, this, &CompetitorTableModel::addCompetitor);
}

void CompetitorTableModel::setParentId(int id)
{
    beginResetModel();
    m_parentId = id;
    endResetModel();
}

void CompetitorTableModel::setEditable(bool editable)
{
    m_editable = editable;
}

bool CompetitorTableModel::editable()
{
    return m_editable;
}

int CompetitorTableModel::rowCount(const QModelIndex &) const
{
    return m_controller->competitors(m_parentId).size();
//      return m_controller->size(m_parentId);


//    if(m_parentId != -1)
//        return JMApp()->competitorController()->size(m_parentId);
//    else
//        return JMApp()->competitorController()->competitors().size();
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
                return QVariant("Wt.");
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
    const QList<Competitor *> competitors = m_controller->competitors(m_parentId);
//    const QList<Competitor *> competitors = JMApp()->competitorController()->competitors(m_parentId);
    const Competitor *judoka = competitors.at(index.row());
    switch(role)
    {
        case Qt::BackgroundRole:
//            if(index.column() == 5)
//            {
//                return QVariant(rankToColor(judoka->rank()));
//            }
            return QVariant(this->columnBackground(judoka, index.column()));

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
        case Qt::UserRole:
            return QVariant(judoka->id());
            break;
    }

    return QVariant();
}

Qt::ItemFlags CompetitorTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    int col = index.column();
    if(m_editable && (col == 0 || col == 1))
    {
        flags |= Qt::ItemIsEditable;
    }

    // TODO: Refine when these flags are set (i.e. based on set data members)
    flags |= Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;

    return flags;
}

bool CompetitorTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool updated = false;

    const QList<Competitor *> competitors = m_controller->competitors(m_parentId);
//    const QList<Competitor *> competitors = JMApp()->competitorController()->competitors(m_parentId);
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

Qt::DropActions CompetitorTableModel::supportedDragActions() const
{
    qDebug() << "CompetitorTableMode::supportedDragActions( " << this << " )";
    return Qt::CopyAction;
}

Qt::DropActions CompetitorTableModel::supportedDropActions() const
{
    qDebug() << "CompetitorTableMode::supportedDropActions( " << this << " )";
    return Qt::CopyAction | Qt::MoveAction | Qt::LinkAction;
}

QStringList CompetitorTableModel::mimeTypes() const
{
    QStringList types;
    types << "application/jm.comp.list";

    return types;
}

QMimeData *CompetitorTableModel::mimeData(const QModelIndexList &indexes) const
{
    const QList<Competitor *> competitors = m_controller->competitors(m_parentId);
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    QHash<int, int> competitorIds;

    foreach(const QModelIndex& index, indexes)
    {
        Competitor *competitor = competitors.at(index.row());
        if(competitor && !competitorIds.contains(competitor->id()))
        {
            competitorIds[competitor->id()] = 1;
            stream << competitor->id();
            qDebug() << "CompetitorTableModel::mimeData() Adding id " << competitor->id() << " to the mime data";
        }

    }

    mimeData->setData("application/jm.comp.list", encodedData);

    return mimeData;
}

bool CompetitorTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << "CompetitorTableModel::dropMimeData(data: " << data << ", action: " << action << ", row: " << row << ", col: " << column << ", parent: " << parent;

    if(action == Qt::IgnoreAction)
        return true;

//    if(data->hasFormat("application/x-qabstractitemmodeldatalist"))
    if(data->hasFormat("application/jm.comp.list"))
    {
        qDebug() << "Valid Drop Format";
        QByteArray encoded = data->data("application/jm.comp.list");
        QDataStream stream(&encoded, QIODevice::ReadOnly);

        while (!stream.atEnd())
        {

            int compId;
            stream >> compId;
            qDebug() << "Dropping Competitor Id: " << compId;

            // Find the Competitor
            // TODO - Needs to be reworked
            const QList<Competitor *> competitors = m_controller->competitors();
            const Competitor *competitor = 0;
            foreach(const Competitor *c, competitors)
            {
                if(c->id() == compId)
                {
                    competitor = c;
                    break;
                }
            }

            if(competitor && (0 != dynamic_cast<BracketController *>(m_controller)))
            {
                // We know we have a bracket controller, now get the bracket.
                Bracket* bracket = dynamic_cast<Bracket *>(m_controller->find(m_parentId));
                if(bracket)
                {
                    // Now add the competitor to the bracket.
                    // TODO: Add the Competitor to the right row based on the drop location.
                    bracket->addCompetitor(new Competitor(*competitor));
                    beginInsertRows(QModelIndex(), bracket->competitors().size(), bracket->competitors().size());
                    endInsertRows();
                    return true;
                }
            }
        }
    }
    else
    {
        qDebug() << "INVALID FORMAT";
    }
    return false;
}

void CompetitorTableModel::addCompetitor(Competitor *competitor)
{
   if(m_parentId == -1 || m_parentId == competitor->clubId())
   {
       int numCompetitors = m_controller->competitors(m_parentId).size() - 1;
//       int numCompetitors = JMApp()->competitorController()->size(m_parentId) - 1;
       beginInsertRows(QModelIndex(), numCompetitors, numCompetitors);
       endInsertRows();
   }
}

QVariant CompetitorTableModel::columnBackground(const Competitor* judoka, int col) const
{
    switch(col)
    {
        case 0:
            if(judoka->firstName().isEmpty())
                return QVariant(QColor(Qt::red));
            break;
        case 1:
            if(judoka->lastName().isEmpty())
                return QVariant(QColor(Qt::red));
            break;

        case 3: // Age
            if(judoka->age() <= 0)
                return QVariant(QColor(Qt::red));
            break;

        case 4: // Weight
            if(judoka->weight() <= 0.0)
                return QVariant(QColor(Qt::red));
            break;

        case 5:
            return QVariant(rankToColor(judoka->rank()));
    }

    return QVariant();
}
