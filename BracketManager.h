#ifndef BRACKETMANAGER_H
#define BRACKETMANAGER_H

#include <QWidget>

class Bracket;
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
    void tournamentChanged();
    void rowChanged ( const QModelIndex & current, const QModelIndex & previous );
    void competitorFilterChanged(const CompetitorFilter& filter);
    void removeCompetitorFromBracket();

private:
    Ui::BracketManager *ui;
    Bracket *m_currentBracket;
};

#endif // BRACKETMANAGER_H
