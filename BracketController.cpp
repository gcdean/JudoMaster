#include "BracketController.h"

#include "Bracket.h"
#include "Tournament.h"

#include "JudoMasterApplication.h"  // DEBUG ONLY. DELETE
#include "Competitor.h"             // DEBUG ONLY. DELETE

#include <QList>

namespace
{
    const QList<Bracket *> NOBRACKETS;
}

BracketController::BracketController(QObject *parent)
    : BaseController(parent)
{
}

const QList<Bracket *> *BracketController::brackets() const
{
    if(!tournament())
        return &NOBRACKETS;

    return &tournament()->brackets();
}

int BracketController::size() const
{
    if(!tournament())
        return 0;

    return tournament()->brackets().size();
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

    // TODO - Remove Below Codel.
    /// START DEBUG
    Competitor* tc = dynamic_cast<Competitor *>(JMApp()->competitorController()->find(1));
    bracket->addCompetitor(tc);
    /// END DEBUG
    tournament()->brackets().append(bracket);
    emit addedDataObj(bracket);

}

void BracketController::remove(int id)
{
    Q_UNUSED(id);
}

const QList<Competitor *> BracketController::competitors(int parentId) const
{
    if(!tournament())
        return QList<Competitor *>();

    if(parentId != -1)
    {
        // First, find the bracket.
        foreach(Bracket *bracket, tournament()->brackets())
        {
            if(bracket->id() == parentId)
            {
                return bracket->competitors();
            }
        }
        return QList<Competitor *>();
    }

    const QList<Competitor *> allComps = JMApp()->competitorController()->competitors();

    return allComps;
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

