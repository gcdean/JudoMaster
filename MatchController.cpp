#include "MatchController.h"

#include "Match.h"
#include "Tournament.h"

MatchController::MatchController(QObject *parent)
    : BaseController(parent)
{
}


void MatchController::add(int parentId)
{

    Match *match = new Match(findNextId());
    match->setBracketId(parentId);

    tournament()->matches().append(match);

    emit addedDataObj(match);
}

JMDataObj *MatchController::find(int id) const
{
    foreach(Match *match, tournament()->matches())
    {
        if(id == match->id())
        {
            return match;
        }
    }
}

int MatchController::findNextId()
{
    int nextId = 0;
    if(tournament())
    {
        foreach (Match* match, tournament()->matches())
        {

            nextId = std::max(nextId, match->id());
        }
    }

    // We now have the max match id.
    nextId++;

    return nextId;
}

void MatchController::remove(int id)
{
}

int MatchController::size() const
{
    return size(-1);
}

int MatchController::size(int id) const
{
    return matches(id).size();
}

const QList<Match *> MatchController::matches(int bracketId) const
{
    if(bracketId == -1)
        return tournament()->matches();

    // TODO Need a better way to hold this list.
    QList<Match *> matches;
    foreach(Match *match, tournament()->matches())
    {
        if(bracketId == match->bracketId())
        {
            matches.append(match);
        }
    }

    return matches;
}



int MatchController::indexOf(int id)
{
    int index = 0;
    foreach(Match *match, tournament()->matches())
    {
        if(id == match->id())
        {
            return index;
        }
        index++;
    }

    return -1;
}
