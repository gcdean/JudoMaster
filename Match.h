#ifndef MATCH_H
#define MATCH_H

#include "JMDataObj.h"

#include <QList>
#include <QString>

class Competitor;

void writeMatchHeader(QTextStream &stream);

class Match : public JMDataObj
{
public:
    Match();
    Match(int id);

    int bracketId() const;
    void setBracketId(int id);
    const Competitor *competitor1() const;
    void setCompetitor1(Competitor *competitor);
    const Competitor *competitor2() const;
    void setCompetitor2(Competitor *competitor);
    const Competitor *winner() const;
    void setWinner(Competitor *competitor);
    int score() const;
    void setScore(int score);
    const QString notes() const;
    void setNotes(QString notes);

    void read(const QJsonObject& json, const QList<Competitor *> competitors);
    // JMDataObj interface
    void read(const QJsonObject &json) override;
    void write(QJsonObject &json) const override;
    void write(QTextStream &stream) const override;

private:
    int m_bracketId;
    Competitor *m_competitor1;  // White
    Competitor *m_competitor2;  // Blue
    Competitor *m_winner;
    int m_score;
    QString m_notes;
};

#endif // MATCH_H
