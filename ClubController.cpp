#include "ClubController.h"

ClubController::ClubController(QObject *parent) :
    QObject(parent)
{
}

void ClubController::setTournament(Tournament *tournament)
{
    m_tournament = tournament;
    emit tournamentChanged();
}

void ClubController::addClub(Club &club)
{
    if(!m_tournament)
        return;

    Club *newClub = new Club(club);
    m_tournament->clubs().append(newClub);
    emit clubAdded(newClub);
}

void ClubController::updateClub(Club& club)
{
    if(!m_tournament)
        return;

    Club* foundClub = findClub(club.id());
    // Remove the old one and insert the new one?
    if(!foundClub)
    {
        return;
    }

    *foundClub = club;

    emit clubUpdated(foundClub);
}

void ClubController::removeClub(int clubId)
{
    if(!m_tournament)
        return;

    Club *foundClub = findClub(clubId);
    if(foundClub)
    {
        m_tournament->clubs().removeOne(foundClub);
        // May need to delete club which means signature of signal changes
        emit clubRemoved(foundClub);
    }
}

const QList<Club *> *ClubController::clubs() const
{
    if(!m_tournament)
        return 0;
    return &m_tournament->clubs();
}

Club* ClubController::findClub(int id)
{
    Club* club = 0;

    for(int x = 0; x < m_tournament->clubs().size() && !club; x++)
    {
        Club* temp = m_tournament->clubs()[x];
        if(temp->id() == id)
        {
            club = temp;
        }
    }
    return club;
}
