#ifndef COMPETITORCONTROLLER_H
#define COMPETITORCONTROLLER_H

#include "BaseController.h"
#include <QObject>

class Competitor;

/**
 * @brief Manages Competitors
 *
 */
class CompetitorController : public BaseController
{
    Q_OBJECT
public:
    explicit CompetitorController(QObject *parent = 0);

//    void createClubCompetitor(int clubId);

    int size() const /*override*/;
    int size(int id) const /*override*/;

    const QList<Competitor *> clubCompetitors(int clubId) const;
    const QList<Competitor *> competitors(int parentId = -1) const override;
//    Competitor* find(int id);       // Should this go to the base class as a generic?
    JMDataObj* find(int id) override;
    void add(int parentId) override;
//    void remove(int id) override;

signals:
    void competitorAdded(Competitor *competitor);

public slots:


protected:
    int findNextId() /*override*/;

};

#endif // COMPETITORCONTROLLER_H
