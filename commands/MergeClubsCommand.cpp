#include "MergeClubsCommand.h"

#include "Club.h"
#include "JudoMasterApplication.h"

#include <QDebug>
#include <QMessageBox>

MergeClubsCommand::MergeClubsCommand(Club *src, Club *dest)
    :BaseCommand()
    , m_srcClub(src)
    , m_destClub(dest)
{
}


bool MergeClubsCommand::run()
{
    if(!m_srcClub || !m_destClub)
        return false;

    qDebug() << "Merging " << m_srcClub->clubName() << " with " << m_destClub->clubName();

    // Confirm the Merge
    QMessageBox::question(0, "Merge Clubs", QString("Are you sure you want to merge %1 with %2").arg(m_srcClub->clubName()).arg(m_destClub->clubName()));

    // Copy Competitors from src to dest.

    foreach(Competitor *cmp, JMApp()->clubController()->competitors(m_srcClub->id()))
    {
        m_destClub->addCompetitor(*cmp);
    }

    // Delete the src club.
    JMApp()->competitorController()->remove(m_srcClub->id());
    return true;
}
