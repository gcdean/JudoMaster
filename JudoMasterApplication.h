#ifndef JUDOMASTERAPPLICATION_H
#define JUDOMASTERAPPLICATION_H

#include "ClubController.h"
#include <QApplication>

class JudoMasterApplication : public QApplication
{
public:
    explicit JudoMasterApplication(int& argc, char** argv);

    ClubController* clubController()  {return &m_clubController;}

private:
    ClubController m_clubController;

};

static JudoMasterApplication *JMApp() {return dynamic_cast<JudoMasterApplication *>(qApp);}
#endif // JUDOMASTERAPPLICATION_H
