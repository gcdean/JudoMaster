#include "CompetitorController.h"
#include "JMUtil.h"

#include <QString>

CompetitorController::CompetitorController(QObject *parent) :
    QObject(parent)
{
}

void CompetitorController::setTournament(Tournament *tournament)
{
    m_tournament = tournament;
}

void CompetitorController::createClubCompetitor(int clubId)
{
    int compId = findNextId();
    Competitor *competitor = new Competitor(compId, QString("Competitor"), QString("%1").arg(compId), JM::Female, 0, 0, JM::White, clubId);
    m_tournament->competitors().append(competitor);

    emit competitorAdded(competitor);
}

int CompetitorController::numClubCompetitors(int clubId) const
{
    int numCompetitors = 0;
    if(clubId == -1)
    {
        numCompetitors = m_tournament->competitors().size();
    }
    else
    {
        foreach(Competitor *competitor, m_tournament->competitors())
        {
            if(competitor->clubId() == clubId)
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

    foreach(Competitor *competitor, m_tournament->competitors())
    {
        if(competitor->clubId() == clubId)
        {
            competitors.append(competitor);
        }
    }

    return competitors;
}

const QList<Competitor *> CompetitorController::competitors(int clubId) const
{
    if(!m_tournament)
    {
        return QList<Competitor *>();
    }
    if(clubId == -1)
        return m_tournament->competitors();
    else
    {
        QList<Competitor *> competitors;

        foreach(Competitor *competitor, m_tournament->competitors())
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
    foreach(Competitor* competitor, m_tournament->competitors())
    {
        id = std::max(id, competitor->id());
    }

    return id + 1;
}
