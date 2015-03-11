#ifndef BRACKETCONTROLLER_H
#define BRACKETCONTROLLER_H

#include "BaseController.h"
#include <QObject>

class Bracket;

class BracketController : public BaseController
{
    Q_OBJECT

public:
    BracketController(QObject *parent = 0);

    const QList <Bracket *> *brackets() const;

    // Overrides
    int size() const override;
    int size(int id) const override;

    // BaseController interface
    void add(int parentId) override;
    void remove(int id) override;
    void removeIndex(int index) override;
    JMDataObj *find(int id) const override;
    int indexOf(int id);

    void removeCompetitorFromBracket(int bracketId, int competitorId);

    const QList<Competitor *> competitors(int parentId = -1) const override;
    const QList<Bracket *> competitorBrackets(int competitorId) const;

signals:
    void competitorRemoved(int index);

private:
    int findNextId() override;

};

#endif // BRACKETCONTROLLER_H
