#ifndef COMPETITORFILTER_H
#define COMPETITORFILTER_H

#include <QString>

class CompetitorFilter
{
public:
    CompetitorFilter();
    CompetitorFilter(int minAge, int maxAge, double minWeight, double maxWeight, QString lastName, bool male=true, bool female=true);
    CompetitorFilter(const CompetitorFilter& src);
    ~CompetitorFilter();

    int minAge() const;
    int maxAge() const;
    double minWeight() const;
    double maxWeight() const;
    QString lastName() const;
    bool male() const;
    bool female() const;

private:
    int m_minAge;
    int m_maxAge;
    double m_minWeight;
    double m_maxWeight;
    QString m_lastName;
    bool m_male;
    bool m_female;
};

#endif // COMPETITORFILTER_H
