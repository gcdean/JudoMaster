#ifndef COMPETIRORFILTER_H
#define COMPETIRORFILTER_H

#include "CompetitorFilter.h"

#include <QWidget>

namespace Ui {
class CompetitorFilterWidget;
}

class CompetitorFilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CompetitorFilterWidget(QWidget *parent = 0);
    ~CompetitorFilterWidget();

Q_SIGNALS:
    void applyFilter(const CompetitorFilter& filter);

private Q_SLOTS:
    void clearFilters();
    void apply();

private:
    Ui::CompetitorFilterWidget *ui;
};

#endif // COMPETIRORFILTER_H
