#ifndef BRACKETEDITOR_H
#define BRACKETEDITOR_H

#include <QWidget>

namespace Ui {
class BracketEditor;
}

class BracketEditor : public QWidget
{
    Q_OBJECT

public:
    explicit BracketEditor(QWidget *parent = 0);
    ~BracketEditor();

private:
    Ui::BracketEditor *ui;
};

#endif // BRACKETEDITOR_H
