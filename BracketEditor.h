#ifndef BRACKETEDITOR_H
#define BRACKETEDITOR_H

#include <QDialog>

namespace Ui {
class BracketEditor;
}

class Bracket;
class MatchTableModel;

class BracketEditor : public QDialog
{
    Q_OBJECT

public:
    explicit BracketEditor(Bracket *bracket, QWidget *parent = 0);
    ~BracketEditor();

    // QDialog interface
public slots:
    virtual void accept();

private slots:
    void addMatch();
    void removeMatch();

private:
    Ui::BracketEditor *ui;
    Bracket *m_bracket;
    MatchTableModel *m_matchTableModel;

};

#endif // BRACKETEDITOR_H
