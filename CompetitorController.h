#ifndef COMPETITORCONTROLLER_H
#define COMPETITORCONTROLLER_H

#include "Competitor.h"
#include "Tournament.h"
#include <QObject>

/**
 * @brief Manages Competitors
 *
 */
class CompetitorController : public QObject
{
    Q_OBJECT
public:
    explicit CompetitorController(QObject *parent = 0);

    void setTournament(Tournament* tournament);
    void createClubCompetitor(int clubId);
    int numClubCompetitors(int clubId) const;
    const QList<Competitor *> clubCompetitors(int clubId) const;
    const QList<Competitor *> competitors(int clubId = -1) const;

signals:
    void competitorAdded(Competitor *competitor);

public slots:

private:
    int findNextId();

private:
    Tournament *m_tournament;
};

#endif // COMPETITORCONTROLLER_H
