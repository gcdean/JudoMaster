#ifndef JUDOMASTERAPPLICATION_H
#define JUDOMASTERAPPLICATION_H

#include "BracketController.h"
#include "ClubController.h"
#include "CompetitorController.h"
#include "MatchController.h"

#include <QApplication>

class Tournament;

class JudoMasterApplication : public QApplication
{
public:
    explicit JudoMasterApplication(int& argc, char** argv);

    ClubController* clubController()  {return &m_clubController;}
    CompetitorController *competitorController() {return &m_competitorController;}
    BracketController *bracketController() {return &m_bracketController;}
    MatchController *matchController() {return &m_matchController;}
    void setTournament(Tournament *tournament);
    const Tournament *tournament() const;

private:
    ClubController m_clubController;
    CompetitorController m_competitorController;
    BracketController m_bracketController;
    MatchController m_matchController;
    Tournament *m_tournament;
};

static JudoMasterApplication *JMApp() {return dynamic_cast<JudoMasterApplication *>(qApp);}
#endif // JUDOMASTERAPPLICATION_H
