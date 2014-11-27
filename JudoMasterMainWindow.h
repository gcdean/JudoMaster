#ifndef JUDOMASTERMAINWINDOW_H
#define JUDOMASTERMAINWINDOW_H

#include <QDir>
#include <QMainWindow>
#include <QString>

class Tournament;
namespace Ui {
class JudoMasterMainWindow;
}

class JudoMasterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JudoMasterMainWindow(QWidget *parent = 0);
    ~JudoMasterMainWindow();

public slots:
    void nameChanged();
    void save();
    void saveAs();
    void newTournament();

private:
    bool getFilename();

private:
    Ui::JudoMasterMainWindow *ui;

    Tournament* m_tournament;
    QString m_fileName;
    QDir m_saveDir;
};

#endif // JUDOMASTERMAINWINDOW_H
