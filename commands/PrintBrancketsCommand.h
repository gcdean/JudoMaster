#ifndef PRINTBRANCHESCOMMAND_H
#define PRINTBRANCHESCOMMAND_H

#include "commands/BaseCommand.h"
#include <QList>

class Bracket;

class PrintBracketsCommand : public BaseCommand
{
public:
    PrintBracketsCommand(QList<Bracket *>brackets);
    ~PrintBracketsCommand();

    // BaseCommand interface
    bool run();

private:
    QList<Bracket *> m_brackets;
};

#endif // PRINTBRANCHESCOMMAND_H
