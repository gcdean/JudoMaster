#ifndef PRINTREGISTRATIONCOMMAND_H
#define PRINTREGISTRATIONCOMMAND_H

#include "BaseCommand.h"
#include <QList>

class QWidget;
class Club;

class PrintRegistrationCommand : public BaseCommand
{
public:
    PrintRegistrationCommand(QWidget *parent = 0, QList<Club *>clubs=QList<Club *>());
    ~PrintRegistrationCommand();

    // BaseCommand interface
public:
    bool run();

private:
    QList<Club *> getClubs();

private:
    QWidget* m_parent;
    QList<Club *> m_clubs;
};

#endif // PRINTREGISTRATIONCOMMAND_H
