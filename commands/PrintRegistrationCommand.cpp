#include "PrintRegistrationCommand.h"

#include "Club.h"
#include "Competitor.h"
#include "JudoMasterApplication.h"

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

PrintRegistrationCommand::PrintRegistrationCommand(QWidget *parent)
    : m_parent(parent)
{

}

PrintRegistrationCommand::~PrintRegistrationCommand()
{

}

bool PrintRegistrationCommand::run()
{
    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, m_parent);
    dialog->setWindowTitle("Print Document");
//    if (editor->textCursor().hasSelection())
//        dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog->exec() != QDialog::Accepted)
        return false;

    qDebug() << "Print Registration";

//    const QList<Club *> *clubs = JMApp()->clubController()->clubs();
    QPainter painter;
    painter.begin(&printer);
    QRect pageRect = printer.pageRect();
    int firstNamePos = pageRect.width() / 4;
    int agePos = pageRect.width() / 2;
    QFontMetrics fm(painter.font(), &printer);

    int wtPos = agePos + fm.boundingRect("XXX").width();

    const QList<Club *> *clubs = JMApp()->clubController()->clubs();

    QList<Club *>sortedClubs(*clubs);
    std::sort(sortedClubs.begin(), sortedClubs.end(), compareClubs);

    bool firstClub = true;
    foreach(const Club* club, sortedClubs)
    {
        if(!firstClub)
            printer.newPage();
        else
            firstClub = false;

        QRect boundRect = fm.boundingRect(club->clubName());
        int left = pageRect.center().x() - boundRect.width() / 2;
        painter.drawText(left, pageRect.top(), club->clubName());

        int top = pageRect.top() + (boundRect.height() * 2);

        painter.drawText(pageRect.left(), top, "Last Name");
        painter.drawText(firstNamePos, top, "First Name");
        painter.drawText(agePos, top, "Age");
        painter.drawText(wtPos, top, "Weight");

        top += boundRect.height();

        QList< Competitor *>sortedCompetitors(JMApp()->competitorController()->competitors(club->id()));
        std::sort(sortedCompetitors.begin(), sortedCompetitors.end(), compareCompetitorNames);
        foreach(const Competitor *competitor, sortedCompetitors)
        {
            // Last Name, First Name    Age Weight Organization, #
            // Names 50% of width, Age, Weight

//            boundRect = fm.boundingRect(name);
            painter.drawText(pageRect.left(), top, competitor->lastName());
            painter.drawText(firstNamePos, top, competitor->firstName());
            painter.drawText(agePos, top, QString("%1").arg(competitor->age()));
            painter.drawText(wtPos, top, QString("%1").arg(competitor->weight()));
            top += boundRect.height();
        }

    }

    painter.end();
    return true;
}

