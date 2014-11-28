#ifndef JUDOMASTERAPPLICATION_H
#define JUDOMASTERAPPLICATION_H

#include "ClubController.h"
#include "CompetitorController.h"

#include <QApplication>

class JudoMasterApplication : public QApplication
{
public:
    explicit JudoMasterApplication(int& argc, char** argv);

    ClubController* clubController()  {return &m_clubController;}
    CompetitorController *competitorController() {return &m_competitorController;}

private:
    ClubController m_clubController;
    CompetitorController m_competitorController;

};

static JudoMasterApplication *JMApp() {return dynamic_cast<JudoMasterApplication *>(qApp);}
#endif // JUDOMASTERAPPLICATION_H
