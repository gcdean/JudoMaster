#ifndef CLUBCONTROLLER_H
#define CLUBCONTROLLER_H

#include "Club.h"
#include "Tournament.h"
#include <QObject>

/**
 * @brief Manages clubs
 */
class ClubController : public QObject
{
    Q_OBJECT
public:
    explicit ClubController(QObject *parent = 0);

    void setTournament(Tournament* tournament);
    void createClub();
    void addClub(Club& club);
    void updateClub(Club& club);
    void removeClub(int clubId);
    const QList <Club *> *clubs() const;

signals:
    void tournamentChanged();
    void clubAdded(Club* club);
    void clubUpdated(Club* club);
    void clubRemoved(Club* club);

public slots:

private:
        Club* findClub(int id);
        int findNextClubId();
private:
    Tournament *m_tournament;
};

#endif // CLUBCONTROLLER_H
