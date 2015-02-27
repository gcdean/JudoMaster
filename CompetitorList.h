#ifndef COMPETITORLIST_H
#define COMPETITORLIST_H

#include <QWidget>

class BaseController;
class QAbstractItemDelegate;
class QAbstractTableModel;

namespace Ui {
class CompetitorList;
}

class QTableView;

class CompetitorList : public QWidget
{
    Q_OBJECT

public:
    explicit CompetitorList(QWidget *parent = 0);
    ~CompetitorList();

    void setClubId(int id);
    void setController(BaseController *controller);
    void setModel(QAbstractTableModel* model);
    QAbstractTableModel* tableModel();
    QTableView* tableView();
    void setTableItemDelegate(QAbstractItemDelegate *delegate);

    bool displayEditButtons();
    void setDisplayEditButtons(bool display);
public slots:
    void tournamentChanged();

private slots:
    void add();
    void remove();

private:
    Ui::CompetitorList *ui;
    int m_clubId;
    BaseController* m_controller;
};

#endif // COMPETITORLIST_H
