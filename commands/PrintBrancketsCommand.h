#ifndef PRINTBRANCHESCOMMAND_H
#define PRINTBRANCHESCOMMAND_H

#include "commands/BaseCommand.h"
#include <QList>

class Tournament;

class PrintBracketsCommand : public BaseCommand
{
public:
    PrintBracketsCommand(Tournament *tournament);
    PrintBracketsCommand(Tournament *tournament, int m_bracket);
    ~PrintBracketsCommand();

    // BaseCommand interface
    bool run();

private:
    Tournament * m_tournament;
    int m_bracket;
};

#endif // PRINTBRANCHESCOMMAND_H
