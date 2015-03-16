#ifndef BRACKETMANAGER_H
#define BRACKETMANAGER_H

#include <QWidget>

class Bracket;
class BracketCompetitorTableModel;
class BracketTableModel;
class BracketTypeItemDelegate;
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
    void viewCompetitor(int logicalIndex);
    void editBracket(int logicalIndex);
    void resetMatCompetitors();

private:
    Ui::BracketManager *ui;
    Bracket *m_currentBracket;
    BracketTableModel *m_bracketModel;
    BracketCompetitorTableModel *m_bracketCompetitorModel;
    BracketTypeItemDelegate *m_bracketItemDelegate;
};

#endif // BRACKETMANAGER_H
