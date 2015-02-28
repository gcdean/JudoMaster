#include "CompetitorFilter.h"

CompetitorFilter::CompetitorFilter()
    : m_minAge(0)
    , m_maxAge(0)
    , m_minWeight(0.0)
    , m_maxWeight(0.0)
{

}

CompetitorFilter::CompetitorFilter(int minAge, int maxAge, double minWeight, double maxWeight)
    : m_minAge(minAge)
    , m_maxAge(maxAge)
    , m_minWeight(minWeight)
      , m_maxWeight(maxWeight)
{

}

CompetitorFilter::CompetitorFilter(const CompetitorFilter &src)
{
    m_minAge = src.minAge();
    m_maxAge = src.maxAge();
    m_minWeight = src.minWeight();
    m_maxWeight = src.maxWeight();
}

CompetitorFilter::~CompetitorFilter()
{

}

int CompetitorFilter::minAge() const
{
    return m_minAge;
}

int CompetitorFilter::maxAge() const
{
    return m_maxAge;
}

double CompetitorFilter::minWeight() const
{
    return m_minWeight;
}

double CompetitorFilter::maxWeight() const
{
    return m_maxWeight;
}

