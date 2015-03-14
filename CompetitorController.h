#ifndef COMPETITORCONTROLLER_H
#define COMPETITORCONTROLLER_H

#include "BaseController.h"
#include "JMUtil.h"
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

    Competitor *createCompetitor(QString firstName, QString lastName, JM::Gender gender, int age , double weight, JM::Rank rank, int clubId);

    int size() const /*override*/;
    int size(int id) const /*override*/;

    Competitor *findByName(QString firstName, QString lastName);

    const QList<Competitor *> clubCompetitors(int clubId) const;
    const QList<Competitor *> competitors(int parentId = -1) const override;
    JMDataObj* find(int id) const override;
    void add(int parentId) override;

signals:
    void competitorAdded(Competitor *competitor);

public slots:


protected:
    int findNextId() /*override*/;

};

#endif // COMPETITORCONTROLLER_H
