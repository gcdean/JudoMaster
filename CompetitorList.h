#ifndef COMPETITORLIST_H
#define COMPETITORLIST_H

#include <QWidget>

class BaseController;
class QAbstractTableModel;

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
    void setController(BaseController *controller);
    void setModel(QAbstractTableModel* model);

private slots:
    void add();
    void remove();
    void tournamentChanged();

private:
    Ui::CompetitorList *ui;
    int m_clubId;
    BaseController* m_controller;
};

#endif // COMPETITORLIST_H
