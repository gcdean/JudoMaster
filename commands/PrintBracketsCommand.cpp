#include "PrintBrancketsCommand.h"

#include "Bracket.h"
#include "JudoMasterApplication.h"
#include "PrintController.h"
#include "Tournament.h"

#include <QDebug>
#include <QList>

PrintBracketsCommand::PrintBracketsCommand(QString tournament)
    : BaseCommand()
    , m_tournament(tournament)
{

}

PrintBracketsCommand::PrintBracketsCommand(QString tournament, QList<int> brackets)
    : BaseCommand()
    , m_tournament(tournament)
{
       m_bracketIds.append(brackets);
}


PrintBracketsCommand::~PrintBracketsCommand()
{

}

bool PrintBracketsCommand::run()
{
    // TODO
    // Open the print dialog
    // Set the print options.

    if(m_bracketIds.size() > 0)
    {
        PrintController pc(m_tournament);
        if (pc.prepare("Print Single Bracket"))
        {
            for(int x = 0; x < m_bracketIds.size(); x++)
            {
                int bracketId = m_bracketIds[x];
                Bracket *bracket = dynamic_cast<Bracket *>(JMApp()->bracketController()->find(bracketId));
                if(bracket)
                {
                    qDebug() << "Print Bracket: " << bracket->name();
                    bool printed = pc.printBracket(bracket);
                    if(printed && x < m_bracketIds.size() - 1)
                        pc.nextPage();
                }
            }
            pc.endPrint();
        }
        else
        {
            qDebug() << "Print failed";
        }
    }
    else if(JMApp()->bracketController()->brackets()->size() > 0)
    {
        PrintController pc(m_tournament);
        if (pc.prepare("Print Brackets"))
        {
            bool newPage = false;
            foreach(Bracket *bracket, *JMApp()->bracketController()->brackets())
            {
                if (bracket->competitors().size() > 1)
                {
                    if (newPage)
                    {
                        pc.nextPage();
                    }

                    newPage = pc.printBracket(bracket);
                    qDebug() << "Print Bracket: " << bracket->name();
                }
                else if (bracket->competitors().size() == 1)
                {
                    qDebug() << "WARNING: Bracket with only one competitor: " << bracket->name();
                }
            }
            pc.endPrint();
        }
        else
        {
            qDebug() << "Printing Failed";
        }
    }
    else
    {
        // print all brackets.
        qDebug() << "Nothing to Print";
    }

    return true;
}

