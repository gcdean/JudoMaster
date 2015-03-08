#ifndef CLUBCONTROLLER_H
#define CLUBCONTROLLER_H

#include "BaseController.h"
#include <QObject>

class Club;

/**
 * @brief Manages clubs
 */
class ClubController : public BaseController
{
    Q_OBJECT
public:
    explicit ClubController(QObject *parent = 0);

    void createClub();

    void updateClub(Club& club);
    void removeClub(int clubId);
    const QList <Club *> *clubs() const;

    // BaseController interface
    void add(int parentId) override;
    int size() const /*override*/;
    int size(int id) const /*override*/;
    void remove(int id);
    void removeIndex(int index);
    int indexOf(int id);

signals:
    void clubAdded(Club* club);
    void clubUpdated(Club* club);
    void clubRemoved(Club* club);

public slots:

private:
    void addClub(Club& club);
    Club* findClub(int id);
    int findNextId() override;

private:
    Tournament *m_tournament;


};

#endif // CLUBCONTROLLER_H
