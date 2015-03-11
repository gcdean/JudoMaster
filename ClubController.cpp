#include "ClubController.h"

#include "Club.h"
#include "Tournament.h"

#include <QDebug>

ClubController::ClubController(QObject *parent) :
    BaseController(parent)
{
}

Club *ClubController::createClub()
{
    int clubId = findNextId();
    Club club(clubId, QString("<Club %1>").arg(clubId), QString("<coach %1>").arg(clubId));
    return addClub(club);
}

Club* ClubController::addClub(Club &club)
{
    if(!tournament())
        return 0;

    Club *newClub = new Club(club);
    tournament()->clubs().append(newClub);
    emit addedDataObj(newClub);

    return newClub;
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
    const QList<Competitor *> NOCOMPETITORS;
}

const QList<Club *> *ClubController::clubs() const
{
    if(!tournament())
        return &NOCLUBS;
    return &tournament()->clubs();
}

Club *ClubController::findClubByName(QString name)
{
    if(!tournament())
        return 0;

    int firstSpace = name.indexOf(' ');
    if(firstSpace != -1)
    {
        qDebug() << "Truncating (" << name << ")";
        name.truncate(firstSpace);
        qDebug() << "Truncated Name is: (" << name << ")";
    }

    foreach(Club *club, tournament()->clubs())
    {
        if(club->clubName().startsWith(name, Qt::CaseInsensitive))
        {
            return club;
        }
    }

    return 0;
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

void ClubController::remove(int id)
{
    removeIndex(indexOf(id));
}

void ClubController::removeIndex(int index)
{
    if(index < 0 || index >= tournament()->clubs().size())
        return;

    emit removedDataObj(tournament()->clubs().at(index));
    tournament()->clubs().removeAt(index);
}

int ClubController::indexOf(int id)
{
    int index = 0;
    foreach(const Club* club, tournament()->clubs())
    {
        if(id == club->id())
            return index;
        index++;
    }

    return -1;
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


JMDataObj *ClubController::find(int id) const
{
    foreach(Club *club, tournament()->clubs())
    {
        if(id == club->id())
            return club;
    }

    return 0;
}

const QList<Competitor *> ClubController::competitors(int parentId) const
{
    Club *club = dynamic_cast<Club *>(find(parentId));

    if(club)
    {
        return club->competitors();
    }

    return NOCOMPETITORS;
}
