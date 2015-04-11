#ifndef CLUBEDITOR_H
#define CLUBEDITOR_H

#include "Club.h"

#include <QWidget>

namespace Ui {
class ClubEditor;
}

class ClubEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ClubEditor(QWidget *parent = 0);
    ~ClubEditor();

signals:
    void clubUpdated(Club *club);

public slots:
    void editClub(Club *club);
    void updateClubName();
    void updateCoachName();
    void updateClub();
    void revertClub();
    void updateStateList();

private:
    void updateControls();

private:
    Ui::ClubEditor *ui;

    Club *m_club;
};

#endif // CLUBEDITOR_H
