#include "BracketController.h"

#include "Bracket.h"
#include "Tournament.h"


BracketController::BracketController(QObject *parent)
    : BaseController(parent)
{
}


int BracketController::size() const
{
    return 0;
}

int BracketController::size(int id) const
{
    Q_UNUSED(id);

    return size();
}

void BracketController::add(int parentId)
{
    Q_UNUSED(parentId);

    if(!tournament())
    {
        return;
    }
    int id = findNextId();
    Bracket *bracket = new Bracket(id);
    tournament()->brackets().append(bracket);
    emit addedDataObj(bracket);

}

void BracketController::remove(int id)
{
    Q_UNUSED(id);
}

int BracketController::findNextId()
{
    int nextId = 0;
    if(tournament())
    {
        foreach (Bracket* bracket, tournament()->brackets())
        {

            nextId = std::max(nextId, bracket->id());
        }
    }

    // We now have the max club id.
    nextId++;

    return nextId;
}

