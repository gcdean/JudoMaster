#include "MatchTableModel.h"

#include "Competitor.h"
#include "JudoMasterApplication.h"
#include "Match.h"

#include <QDebug>

MatchTableModel::MatchTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(JMApp()->matchController(), &BaseController::addedDataObj, this, &MatchTableModel::bracketAdded);
}

void MatchTableModel::setBracketId(int id)
{
    m_bracketId = id;
}

int MatchTableModel::bracketId()
{
    return m_bracketId;
}


int MatchTableModel::rowCount(const QModelIndex &parent) const
{
    const MatchController* controller = JMApp()->matchController();
    return controller->size(m_bracketId);
}

int MatchTableModel::columnCount(const QModelIndex &parent) const
{
    return MatchTableModel::MAX_COLUMNS;
}

QVariant MatchTableModel::data(const QModelIndex &index, int role) const
{
    const QList<Match *> matches = JMApp()->matchController()->matches(m_bracketId);

    if(index.row() >= matches.size())
    {
        return QVariant();
    }

    Match *match = matches[index.row()];

//    qDebug() << "MatchTableModel::data(). Match is: " << match;
    switch(role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
        {
            switch(index.column())
            {
                case MatchTableModel::firstCompetitor:
                {
//                    qDebug() << "Match Competitor 1 is: " << match->competitor1();
                    return QVariant(match->competitor1() ? QString("%1 %2").arg(match->competitor1()->firstName()).arg(match->competitor1()->lastName()) : "<Not Set>");
                }

                case MatchTableModel::secondCompetitor:
                {
//                    qDebug() << "Match Competitor 2 is: " << match->competitor2();
                    return QVariant(match->competitor2() ? QString("%1 %2").arg(match->competitor2()->firstName()).arg(match->competitor2()->lastName()) : "<Not Set>");
                }

                case MatchTableModel::winner:
                {
//                    qDebug() << "Match winner is: " << match->winner();
                    return QVariant(match->winner() ? QString("%1 %2").arg(match->winner()->firstName()).arg(match->winner()->lastName()) : "<Not Set>");
                }

                case MatchTableModel::score:
                    return QVariant(match->score());

                case MatchTableModel::notes:
                    return QVariant(match->notes());
            }
        }
        break;
    }

    return QVariant();
}


bool MatchTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "MatchTableModel::setData(). role is: " << role;

    // TODO - Should use commands here to modify the data.

    const QList<Match *> matches = JMApp()->matchController()->matches(m_bracketId);

    if(index.row() >= matches.size())
    {
        return false;
    }

    Match *match = matches[index.row()];

    bool valid = false;
    switch(index.column())
    {
        case firstCompetitor:
        {
            Competitor *competitor = dynamic_cast<Competitor *>(JMApp()->competitorController()->find(value.toInt()));
            match->setCompetitor1(competitor);
            valid = true;
        }
            break;

        case secondCompetitor:
        {
            Competitor *competitor = dynamic_cast<Competitor *>(JMApp()->competitorController()->find(value.toInt()));
            match->setCompetitor2(competitor);
            valid = true;
        }
            break;

        case winner:
        {
            Competitor *competitor = dynamic_cast<Competitor *>(JMApp()->competitorController()->find(value.toInt()));
            match->setWinner(competitor);
            valid = true;
        }
            break;

        case score:
            match->setScore(value.toInt());
            valid = true;
            break;

        case notes:
            match->setNotes(value.toString());
            valid = true;
    }

    return valid;
}

QVariant MatchTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            switch(section)
            {
                case firstCompetitor:
                    return QVariant("White");

                case secondCompetitor:
                    return QVariant("Blue");

                case winner:
                    return QVariant("Winner");

                case score:
                    return QVariant("Score");

                case notes:
                    return QVariant("Notes");
            }
        }
    }

    return QVariant();
}

void MatchTableModel::bracketAdded(JMDataObj *data)
{
    int index = JMApp()->matchController()->indexOf(data->id());
    beginInsertRows(QModelIndex(), index, index);
    endInsertRows();
}


Qt::ItemFlags MatchTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    flags |= Qt::ItemIsEditable;

    return flags;
}


