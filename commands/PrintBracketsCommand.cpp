#include "PrintBrancketsCommand.h"

#include "Tournament.h"
#include "Bracket.h"
#include "PrintController.h"

#include <QDebug>
#include <QList>

PrintBracketsCommand::PrintBracketsCommand(Tournament * tournament)
    : BaseCommand()
    , m_tournament(tournament)
    , m_bracket(-1)
{

}

PrintBracketsCommand::PrintBracketsCommand(Tournament * tournament, int bracket)
    : BaseCommand()
    , m_tournament(tournament)
    , m_bracket(bracket)
{

}


PrintBracketsCommand::~PrintBracketsCommand()
{

}

bool PrintBracketsCommand::run()
{
    // TODO
    // Open the print dialog
    // Set the print options.

    if ((m_bracket > -1) && (m_bracket < m_tournament->brackets().size()))
    {
        PrintController pc(m_tournament);
        pc.prepare("Print Single Bracket");
        pc.printBracket(m_tournament->brackets()[m_bracket]);
        pc.endPrint();
        qDebug() << "Print Bracket: " << m_tournament->brackets()[m_bracket]->name();
    }
    else if(m_tournament->brackets().size() > 0)
    {
        PrintController pc(m_tournament);
        pc.prepare("Print Brackets");
        bool first = true;
        foreach(Bracket *bracket, m_tournament->brackets())
        {
            if (!first)
            {
                pc.nextPage();
            }
            else
            {
                first = false;
            }

            pc.printBracket(bracket);
            qDebug() << "Print Bracket: " << bracket->name();
        }
        pc.endPrint();
    }
    else
    {
        // print all brackets.
        qDebug() << "Nothing to Print";
    }

    return true;
}

