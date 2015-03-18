#include "PrintRegistrationCommand.h"

#include "Club.h"
#include "Competitor.h"
#include "JudoMasterApplication.h"
#include "PrintController.h"
#include "Tournament.h"

#include <algorithm>
#include <QFontMetrics>
#include <QList>
#include <QPainter>
#include <QtPrintSupport>
#include <QPrintDialog>
#include <QPrinter>
#include <QRect>
#include <QString>
#include <QWidget>

namespace
{
    bool compareClubs(Club* club1, Club* club2)
    {
        return club1->clubName().compare(club2->clubName()) < 0;
    }

    bool compareCompetitorNames(Competitor* competitor1, Competitor* competitor2)
    {
        int lastNameCompare = competitor1->lastName().compare(competitor2->lastName());
        if( lastNameCompare < 0)
        {
            return true;
        }

        if(lastNameCompare == 0)
        {
            // Last names are the same, compare the first name.
            return competitor1->firstName().compare(competitor2->firstName()) < 0;
        }

        return false;
    }
}

PrintRegistrationCommand::PrintRegistrationCommand(QWidget *parent, QList<Club *> clubs)
    : m_parent(parent)
    , m_clubs(clubs)
{

}

PrintRegistrationCommand::~PrintRegistrationCommand()
{

}

bool PrintRegistrationCommand::run()
{

    QList<Club *>sortedClubs = getClubs();

    PrintController pc(JMApp()->tournament()->name(), QPrinter::Portrait);
    pc.prepare("Print Registration");
    bool newPage = false;
    foreach(const Club* club, sortedClubs)
    {
        if(newPage)
            pc.nextPage();

        newPage = pc.printClubRegistration(club);
    }

    return true;
}

QList<Club *> PrintRegistrationCommand::getClubs()
{
    QList<Club *>sortedClubs;

    if(m_clubs.size() == 0)
    {
        const QList<Club *> *clubs = JMApp()->clubController()->clubs();

        sortedClubs.append(*clubs);
    }
    else
    {
        sortedClubs.append(m_clubs);
    }

    std::sort(sortedClubs.begin(), sortedClubs.end(), compareClubs);

    return sortedClubs;
}

