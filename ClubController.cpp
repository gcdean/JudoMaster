#include "ClubController.h"

#include "Club.h"
#include "Tournament.h"

ClubController::ClubController(QObject *parent) :
    BaseController(parent)
{
}

void ClubController::createClub()
{
    int clubId = findNextId();
    Club club(clubId, QString("<Club %1>").arg(clubId), QString("<coach %1>").arg(clubId));
    addClub(club);
}

void ClubController::addClub(Club &club)
{
    if(!tournament())
        return;

    Club *newClub = new Club(club);
    tournament()->clubs().append(newClub);
    //emit clubAdded(newClub);
    emit addedDataObj(newClub);
}

void ClubController::updateClub(Club& club)
{
    if(!tournament())
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
    if(!tournament())
        return;

    Club *foundClub = findClub(clubId);
    if(foundClub)
    {
        tournament()->clubs().removeOne(foundClub);
        // May need to delete club which means signature of signal changes
        emit clubRemoved(foundClub);
    }
}

namespace
{
    const QList<Club *> NOCLUBS;
}
const QList<Club *> *ClubController::clubs() const
{
    if(!tournament())
        return &NOCLUBS;
    return &tournament()->clubs();
}

void ClubController::add(int parentId)
{
    Q_UNUSED(parentId);

    if(!tournament())
        return;

    createClub();
}

int ClubController::size() const
{
    if(!tournament())
    {
        return 0;
    }

    return tournament()->clubs().size();
}

int ClubController::size(int id) const
{
    // For now, just return the size.
    return size();
}

Club* ClubController::findClub(int id)
{
    Club* club = 0;

    if(!tournament())
        return club;

    for(int x = 0; x < tournament()->clubs().size() && !club; x++)
    {
        Club* temp = tournament()->clubs()[x];
        if(temp->id() == id)
        {
            club = temp;
        }
    }
    return club;
}

int ClubController::findNextId()
{
    int nextId = 0;
    if(tournament())
    {
        foreach (Club* club, tournament()->clubs())
        {

            nextId = std::max(nextId, club->id());
        }
    }

    // We now have the max club id.
    nextId++;

    return nextId;
}
