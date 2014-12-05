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

    void setClubId(int id);

private slots:
    void addCompetitor();
    void tournamentChanged();

private:
    Ui::CompetitorList *ui;
    int m_clubId;
};

#endif // COMPETITORLIST_H
