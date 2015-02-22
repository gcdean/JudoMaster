#include "BaseController.h"

#include "Bracket.h"
#include "Competitor.h"
#include "JudoMasterApplication.h"
#include "Tournament.h"

#include <QList>

BaseController::BaseController(QObject *parent) :
    QObject(parent)
  , m_tournament(0)
{
}

void BaseController::setTournament(Tournament *tournament)
{
    m_tournament = tournament;
    emit tournamentChanged();

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

JMDataObj* BaseController::find(int id)
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

const QList<Competitor *> BaseController::competitors(int parentId) const
{
    return QList<Competitor *>();
}
