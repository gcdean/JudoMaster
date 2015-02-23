#ifndef BASECOMMAND_H
#define BASECOMMAND_H


class BaseCommand
{
public:
    BaseCommand();
    ~BaseCommand();

    virtual bool run() = 0;
};

#endif // BASECOMMAND_H
