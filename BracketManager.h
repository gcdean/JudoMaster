#ifndef BRACKETMANAGER_H
#define BRACKETMANAGER_H

#include <QWidget>

namespace Ui {
class BracketManager;
}

class BracketManager : public QWidget
{
    Q_OBJECT

public:
    explicit BracketManager(QWidget *parent = 0);
    ~BracketManager();

private:
    Ui::BracketManager *ui;
};

#endif // BRACKETMANAGER_H
