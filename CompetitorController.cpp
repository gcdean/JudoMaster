#include "CompetitorController.h"
#include "JMUtil.h"

#include "Competitor.h"
#include "Tournament.h"

#include <QString>

CompetitorController::CompetitorController(QObject *parent) :
    BaseController(parent)
{
}

JMDataObj* CompetitorController::find(int id)
{
    // Real simple linear search for now.
    foreach(Competitor* competitor, tournament()->competitors())
    {
        if(competitor->id() == id)
        {
            // Found it!
            return competitor;
        }
    }

    return 0;
}

void CompetitorController::add(int parentId)
{
    int compId = findNextId();
    Competitor *competitor = new Competitor(compId, QString("Competitor"), QString("%1").arg(compId), JM::Female, 0, 0, JM::White, parentId);
    tournament()->competitors().append(competitor);

    emit addedDataObj(competitor);

}

//void CompetitorController::createClubCompetitor(int clubId)
//{
//    int compId = findNextId();
//    Competitor *competitor = new Competitor(compId, QString("Competitor"), QString("%1").arg(compId), JM::Female, 0, 0, JM::White, clubId);
//    tournament()->competitors().append(competitor);

//    emit competitorAdded(competitor);
//}

int CompetitorController::size() const
{
    if(!tournament())
        return 0;

    return tournament()->competitors().size();
}

int CompetitorController::size(int id) const
{
    int numCompetitors = 0;
    if(!tournament())
        return numCompetitors;

    if(id == -1)
    {
        numCompetitors = tournament()->competitors().size();
    }
    else
    {
        foreach(Competitor *competitor, tournament()->competitors())
        {
            if(competitor->clubId() == id)
            {
                numCompetitors++;
            }
        }
    }

    return numCompetitors;
}
/**
 * @brief Returns the list of competitors for a specified club
 * @param clubId
 * @return
 */
const QList<Competitor *> CompetitorController::clubCompetitors(int clubId) const
{
    // CAN DELETE THIS
    QList<Competitor *> competitors;

    if(tournament())
    {
        foreach(Competitor *competitor, tournament()->competitors())
        {
            if(competitor->clubId() == clubId)
            {
                competitors.append(competitor);
            }
        }
    }

    return competitors;
}

const QList<Competitor *> CompetitorController::competitors(int clubId) const
{
    if(!tournament())
    {
        return QList<Competitor *>();
    }
    if(clubId == -1)
        return tournament()->competitors();
    else
    {
        // TODO: I think this should be moved to the Club Controller and this controller
        // should only return all competitors.
        QList<Competitor *> competitors;

        foreach(Competitor *competitor, tournament()->competitors())
        {
            if(competitor->clubId() == clubId)
            {
                competitors.append(competitor);
            }
        }

        return competitors;

    }

}

int CompetitorController::findNextId()
{
    int id = 0;
    if(tournament())
    {
        foreach(Competitor* competitor, tournament()->competitors())
        {
            id = std::max(id, competitor->id());
        }
    }

    return id + 1;
}
