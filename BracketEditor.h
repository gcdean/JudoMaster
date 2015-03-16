#ifndef BRACKETEDITOR_H
#define BRACKETEDITOR_H

#include <QDialog>

namespace Ui {
class BracketEditor;
}

class Bracket;

class BracketEditor : public QDialog
{
    Q_OBJECT

public:
    explicit BracketEditor(Bracket *bracket, QWidget *parent = 0);
    ~BracketEditor();

    // QDialog interface
public slots:
    virtual void accept();

private:
    Ui::BracketEditor *ui;
    Bracket *m_bracket;

};

#endif // BRACKETEDITOR_H
