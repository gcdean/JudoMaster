#ifndef CLUBCONTROLLER_H
#define CLUBCONTROLLER_H

#include "Club.h"
#include "Tournament.h"
#include <QObject>

/*
 * Manages clubs.
 */
class ClubController : public QObject
{
    Q_OBJECT
public:
    explicit ClubController(QObject *parent = 0);

    void setTournament(Tournament* tournament);
    void addClub(Club& club);
    void updateClub(Club& club);
    void removeClub(int clubId);
    const QList <Club *> *clubs() const;

    bool isValid() const {return m_tournament != 0;}

signals:
    void tournamentChanged();
    void clubAdded(Club* club);
    void clubUpdated(Club* club);
    void clubRemoved(Club* club);

public slots:

private:
        Club* findClub(int id);

private:
    Tournament *m_tournament;
};

#endif // CLUBCONTROLLER_H
