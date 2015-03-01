#ifndef PRINTREGISTRATIONCOMMAND_H
#define PRINTREGISTRATIONCOMMAND_H

#include "BaseCommand.h"

class QWidget;

class PrintRegistrationCommand : public BaseCommand
{
public:
    PrintRegistrationCommand(QWidget *parent = 0);
    ~PrintRegistrationCommand();

    // BaseCommand interface
public:
    bool run();

private:
    QWidget* m_parent;
};

#endif // PRINTREGISTRATIONCOMMAND_H
