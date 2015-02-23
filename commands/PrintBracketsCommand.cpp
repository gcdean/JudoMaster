#include "PrintBrancketsCommand.h"

#include "Bracket.h"

#include <QDebug>
#include <QList>

PrintBracketsCommand::PrintBracketsCommand(QList<Bracket *> brackets)
    : BaseCommand()
    , m_brackets(brackets)
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
    if(m_brackets.size() > 0)
    {
        foreach(Bracket *bracket, m_brackets)
        {
            qDebug() << "Print Bracket: " << bracket->name();
        }
    }
    else
    {
        // print all brackets.
        qDebug() << "Print All Brackets";
    }

}

