#ifndef MATCHCONTROLLER_H
#define MATCHCONTROLLER_H

#include "BaseController.h"

class Match;

class MatchController : public BaseController
{
    Q_OBJECT
public:
    MatchController(QObject *parent = 0);

    // BaseController interface
public:
    void add(int parentId) override;
    JMDataObj *find(int id) const override;
    int indexOf(int id) override;
    void remove(int id) override;
    int size() const override;
    int size(int id) const override;

    const QList<Match *> matches(int bracketId) const;

    // BaseController interface
protected:
    virtual int findNextId();

};

#endif // MATCHCONTROLLER_H
