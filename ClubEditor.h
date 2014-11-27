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

public slots:
    void editClub(Club *club);
    void updateClubName();
    void updateCoachName();

private:
    Ui::ClubEditor *ui;

    Club *m_club;
};

#endif // CLUBEDITOR_H
