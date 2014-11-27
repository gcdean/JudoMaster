#ifndef COMPETITORLIST_H
#define COMPETITORLIST_H

#include <QWidget>

namespace Ui {
class CompetitorList;
}

class CompetitorList : public QWidget
{
    Q_OBJECT

public:
    explicit CompetitorList(QWidget *parent = 0);
    ~CompetitorList();

private:
    Ui::CompetitorList *ui;
};

#endif // COMPETITORLIST_H
