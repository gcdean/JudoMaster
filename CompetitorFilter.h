#ifndef COMPETITORFILTER_H
#define COMPETITORFILTER_H


class CompetitorFilter
{
public:
    CompetitorFilter();
    CompetitorFilter(int minAge, int maxAge, double minWeight, double maxWeight);
    CompetitorFilter(const CompetitorFilter& src);
    ~CompetitorFilter();

    int minAge() const;
    int maxAge() const;
    double minWeight() const;
    double maxWeight() const;

private:
    int m_minAge;
    int m_maxAge;
    double m_minWeight;
    double m_maxWeight;
};

#endif // COMPETITORFILTER_H
