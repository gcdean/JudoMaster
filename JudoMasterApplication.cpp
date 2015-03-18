#include "JudoMasterApplication.h"

#include "Tournament.h"

JudoMasterApplication::JudoMasterApplication(int &argc, char **argv) :
    QApplication(argc, argv)
    , m_tournament(0)
{
}

void JudoMasterApplication::setTournament(Tournament *tournament)
{
    m_tournament = tournament;
}

const Tournament *JudoMasterApplication::tournament() const
{
    return m_tournament;
}
