#ifndef PRINTBRANCHESCOMMAND_H
#define PRINTBRANCHESCOMMAND_H

#include "commands/BaseCommand.h"
#include <QList>
#include <QString>

class Tournament;

class PrintBracketsCommand : public BaseCommand
{
public:
    PrintBracketsCommand(QString tournament);
    PrintBracketsCommand(QString tournament, QList<int> brackets);
    ~PrintBracketsCommand();

    // BaseCommand interface
    bool run();

private:
    QString m_tournament;
    QList<int> m_bracketIds;
};

#endif // PRINTBRANCHESCOMMAND_H
