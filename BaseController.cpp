#include "BaseController.h"

#include "Bracket.h"
#include "Competitor.h"
#include "CompetitorFilter.h"
#include "Tournament.h"

#include <QDebug>
#include <QList>

BaseController::BaseController(QObject *parent) :
    QObject(parent)
  , m_tournament(0)
{
}

void BaseController::setTournament(Tournament *tournament)
{
    if(m_tournament != tournament)
    {
        m_tournament = tournament;
        emit tournamentChanged();
    }
}

Tournament *BaseController::tournament() const
{
    return m_tournament;
}

int BaseController::size() const
{
    return 0;
}

int BaseController::size(int id) const
{
    Q_UNUSED(id);
    return 0;
}

void BaseController::add(int parentId)
{
    Q_UNUSED(parentId);
    // Do Nothing.
}

void BaseController::remove(int id)
{
    Q_UNUSED(id);
    // Do Nothing.
}

void BaseController::removeIndex(int index)
{
    Q_UNUSED(index);
}

JMDataObj* BaseController::find(int id) const
{
    Q_UNUSED(id);
    return 0;
}

int BaseController::indexOf(int id)
{
    Q_UNUSED(id);
    return -1;
}

const QList<Competitor *> BaseController::competitors(int parentId) const
{
    Q_UNUSED(parentId);
    return QList<Competitor *>();
}

const QList<Competitor *> BaseController::competitors(const CompetitorFilter &filter, int parentId) const
{
    const QList<Competitor *> allCompetitors = competitors(parentId);

    QList <Competitor *>filteredCompetitors;

//    qDebug() << "There are " << allCompetitors.size() << " Prior to filtering";
    // Now Filter
    foreach(Competitor *competitor, allCompetitors)
    {
        bool add = true;
        if(filter.minAge() > 0 && competitor->age() < filter.minAge())
            add = false;
        if(filter.maxAge() > 0 && competitor->age() > filter.maxAge())
            add = false;
        if(filter.minWeight() > 0.0 && competitor->weight() < filter.minWeight())
            add = false;
        if(filter.maxWeight() > 0.0 && competitor->weight() > filter.maxWeight())
            add = false;
        if(filter.lastName().size() > 0)
        {
            if(!competitor->lastName().startsWith(filter.lastName(), Qt::CaseInsensitive))
                add = false;
        }
        if(filter.male() && competitor->gender() == JM::Female)
            add = false;
        else if(filter.female() && competitor->gender() == JM::Male)
            add = false;

        if(add)
            filteredCompetitors.append(competitor);
    }

    // TODO This is wrong in that a local object is being returned.
    return filteredCompetitors;
}
