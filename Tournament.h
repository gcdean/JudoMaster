#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QDate>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>
#include <QTime>
#include "Club.h"
#include "Competitor.h"

class Tournament : public QObject
{
    Q_OBJECT
public:
    explicit Tournament(QObject *parent = 0);

    QString name() const {return m_name;}
    void setName(QString name) {m_name = name;}
    QDate date() const {return m_date;}
    void setDate(QDate date) {m_date = date;}
    QTime startTime() const {return m_startTime;}
    void setStartTime(QTime startTime) {m_startTime = startTime;}

    QList<Club *>& clubs() {return m_clubs;}

    void read(QJsonObject &json);
    void write(QJsonObject& json) const;

signals:

public slots:

private:
    QString m_name;
    QDate m_date;
    QTime m_startTime;

    QList<Club *> m_clubs;
    QList<Competitor *> m_competitors;

};

#endif // TOURNAMENT_H
