#include "BracketController.h"

#include "Bracket.h"
#include "Competitor.h"
#include "Tournament.h"

#include "JudoMasterApplication.h"  // DEBUG ONLY. DELETE
#include "Competitor.h"             // DEBUG ONLY. DELETE

#include <QDebug>
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

    tournament()->brackets().append(bracket);
    emit addedDataObj(bracket);

}

void BracketController::remove(int id)
{
    if(!tournament())
    {
        return;
    }

    Bracket* bracket = dynamic_cast<Bracket *>(find(id));
    if(bracket)
    {
        emit removedDataObj(bracket);
        tournament()->brackets().removeOne(bracket);
    }
}

void BracketController::removeIndex(int index)
{
    if(!tournament() || index < 0 || index >= tournament()->brackets().size())
    {
        return;
    }

    emit removedDataObj(tournament()->brackets().at(index));
    tournament()->brackets().removeAt(index);
}



JMDataObj* BracketController::find(int id) const
{
    foreach (Bracket *bracket, tournament()->brackets())
    {
        if(bracket->id() == id)
        {
            return bracket;
        }
    }

    return 0;
}

int BracketController::indexOf(int id)
{
    int index = 0;
    foreach (Bracket *bracket, tournament()->brackets())
    {
        if(bracket->id() == id)
        {
            return index;
        }
        index++;
    }

    return -1;
}

void BracketController::removeCompetitorFromBracket(int bracketId, int competitorId)
{
    qDebug() << "BracketController - Remove competitor " << competitorId << " from Bracket " << bracketId;
    Bracket *bracket = dynamic_cast<Bracket *>(find(bracketId));
    if(bracket)
    {
        int index = 0;
        foreach(Competitor *competitor, bracket->competitors())
        {
            if(competitor->id() == competitorId)
            {
                bracket->removeCompetitor(index);
                emit competitorRemoved(index);
                break;
            }
            index++;
        }
    }
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

const QList<Bracket *> BracketController::competitorBrackets(int competitorId) const
{
    // Find the brackets that the specified competitor is in.
    QList <Bracket *> brackets;
    foreach(Bracket *bracket, tournament()->brackets())
    {
        foreach(Competitor *competitor, bracket->competitors())
        {
            if(competitorId == competitor->id())
            {
                brackets.append(bracket);
                break;
            }
        }
    }

    return brackets;
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

