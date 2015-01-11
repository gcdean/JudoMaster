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

    void createClubCompetitor(int clubId);

    int size() const /*override*/;
    int size(int id) const /*override*/;

    const QList<Competitor *> clubCompetitors(int clubId) const;
    const QList<Competitor *> competitors(int clubId = -1) const;

signals:
    void competitorAdded(Competitor *competitor);

public slots:


protected:
    int findNextId() /*override*/;

};

#endif // COMPETITORCONTROLLER_H
