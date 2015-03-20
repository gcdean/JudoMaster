#ifndef BRACKETMANAGER_H
#define BRACKETMANAGER_H

#include <QWidget>

class Bracket;
class BracketCompetitorTableModel;
class BracketTableModel;
class BracketTypeItemDelegate;
class CompetitorFilter;
class CompetitorTableModel;
class PrintBracketsAction;

class QSortFilterProxyModel;

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
    void editBracket();
    void editCompetitor();
    void resetMatCompetitors();
    void bracketContextMenu(const QPoint & pos);
    void printSelectedBrackets();

private:
    CompetitorTableModel *allCompetitorModel();

private:
    Ui::BracketManager *ui;
    Bracket *m_currentBracket;
    BracketTableModel *m_bracketModel;
    BracketCompetitorTableModel *m_bracketCompetitorModel;
    BracketTypeItemDelegate *m_bracketItemDelegate;
    PrintBracketsAction *m_printAction;
    QAction *m_editBracketAction;
    CompetitorTableModel *m_allCompModel;
    QSortFilterProxyModel*m_allCompSortModel;
};

#endif // BRACKETMANAGER_H
