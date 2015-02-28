#ifndef BRACKETMANAGER_H
#define BRACKETMANAGER_H

#include <QWidget>

class CompetitorFilter;

namespace Ui {
class BracketManager;
}

class BracketManager : public QWidget
{
    Q_OBJECT

public:
    explicit BracketManager(QWidget *parent = 0);
    ~BracketManager();

private Q_SLOTS:
    void addBracket();
    void bracketChanged(const QModelIndex &current, const QModelIndex &previous);
    void tournamentChanged();
    void rowChanged ( const QModelIndex & current, const QModelIndex & previous );
    void competitorFilterChanged(const CompetitorFilter& filter);

private:
    Ui::BracketManager *ui;
};

#endif // BRACKETMANAGER_H
