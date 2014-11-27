#ifndef CLUBSEDITOR_H
#define CLUBSEDITOR_H

#include "Club.h"

#include <QWidget>
#include <QList>


namespace Ui {
class ClubsEditor;
}

class ClubsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ClubsEditor(QWidget *parent = 0);
    ~ClubsEditor();

    void setClubs(QList<Club *>* clubs);

signals:
    void clubAdded(Club *club);
    void clubSelect(Club *club);

private slots:
    void addClub();
    void clubSelected(const QModelIndex &index);

private:
    Ui::ClubsEditor *ui;

//    QList<Club *>* m_clubs;
};

#endif // CLUBSEDITOR_H
