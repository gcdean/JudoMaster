#include "JudoMasterMainWindow.h"
#include "ui_JudoMasterMainWindow.h"

#include "Bracket.h"
#include "CompetitorController.h"
#include "JudoMasterApplication.h"
#include "Tournament.h"
#include "actions/PrintBracketsAction.h"
#include "commands/PrintBrancketsCommand.h"
#include "commands/PrintRegistrationCommand.h"

#include <QDate>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>
#include <QHash>
#include <QJsonObject>
#include <QStringList>
#include <QTextStream>

#include <QDebug>



JudoMasterMainWindow::JudoMasterMainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::JudoMasterMainWindow)
    , m_printBracketsAction(0)
    , m_tournament(0)
{
    ui->setupUi(this                                            );

    m_saveDir = QDir::home();


    ui->tabWidget->setTabText(0, QString("General"));
    ui->tabWidget->setTabText(1, QString("Brackets"));

    m_printBracketsAction = new PrintBracketsAction(this);
    ui->menuPrint->addAction(m_printBracketsAction);

    connect(ui->actionNew, &QAction::triggered, this, &JudoMasterMainWindow::newTournament);
    connect(ui->actionSave_As, &QAction::triggered, this, &JudoMasterMainWindow::saveAs);
    connect(ui->actionSave, &QAction::triggered, this, &JudoMasterMainWindow::save);
    connect(ui->actionClose, &QAction::triggered, this, &JudoMasterMainWindow::close);
    connect(ui->actionOpen, &QAction::triggered, this, &JudoMasterMainWindow::open);
    connect(ui->actionPrint_Registration, &QAction::triggered, this, &JudoMasterMainWindow::printRegistration);
    connect(m_printBracketsAction, &QAction::triggered, this, &JudoMasterMainWindow::printBrackets);
    connect(ui->actionImport, &QAction::triggered, this, &JudoMasterMainWindow::import);

    connect(ui->tournamentName, &QLineEdit::editingFinished, this, &JudoMasterMainWindow::nameChanged);
    connect(ui->tournamentDate, &QDateTimeEdit::dateChanged, this, &JudoMasterMainWindow::dateChanged);
    connect(ui->startTime, &QDateTimeEdit::timeChanged, this, &JudoMasterMainWindow::timeChanged);

    connect(JMApp(), &QCoreApplication::aboutToQuit, this, &JudoMasterMainWindow::close);
    updateControls();
}

JudoMasterMainWindow::~JudoMasterMainWindow()
{
    delete ui;
}

void JudoMasterMainWindow::nameChanged()
{
    if(!m_tournament)
    {
        return;
    }

    m_tournament->setName(ui->tournamentName->text());
}

void JudoMasterMainWindow::dateChanged(const QDate &date)
{
    if(!m_tournament)
    {
        return;
    }

    m_tournament->setDate(date);
}

void JudoMasterMainWindow::timeChanged(const QTime &time)
{
    if(!m_tournament)
    {
        return;
    }

    m_tournament->setStartTime(time);
}


void JudoMasterMainWindow::save()
{
    if(m_tournament->fileName().isEmpty())
//    if(m_fileName.isEmpty())
    {
        if(!getFilename())
            return;
    }

    QFile saveFile(m_tournament->fileName());

    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open file for writing");
    }


    QJsonObject trnObj;
    m_tournament->write(trnObj);

    QJsonDocument saveDoc(trnObj);
    saveFile.write(saveDoc.toJson());

}

void JudoMasterMainWindow::saveAs()
{
    if(!m_tournament)
        return;

    if(getFilename())
        save();
}

void JudoMasterMainWindow::newTournament()
{
    if(m_tournament)
    {
        delete m_tournament;
    }
    m_tournament = new Tournament();
    m_tournament->setName("Test");
    QDate trnDate(2015, 3, 15);
    m_tournament->setDate(trnDate);

    JMApp()->clubController()->setTournament(m_tournament);
    JMApp()->competitorController()->setTournament(m_tournament);
    JMApp()->bracketController()->setTournament(m_tournament);

    updateControls();
}

void JudoMasterMainWindow::close()
{
    // Check to see if we need to save.

    JMApp()->clubController()->setTournament(0);
    JMApp()->competitorController()->setTournament(0);
    JMApp()->bracketController()->setTournament(0);

    delete m_tournament;
    m_tournament = 0;
    updateControls();
}

void JudoMasterMainWindow::open()
{
    QString openFileName = QFileDialog::getOpenFileName(this, "Open JudoMaster Tournament File", m_saveDir.absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");

    if(openFileName.isEmpty())
    {
        return;
    }

    loadFile(openFileName);
    updateControls();
}

void JudoMasterMainWindow::printBrackets()
{
    QList<Bracket *> brackets;
   PrintBracketsCommand cmd(brackets);
   cmd.run();
}

void JudoMasterMainWindow::printRegistration()
{
    PrintRegistrationCommand cmd(this);
    cmd.run();
}

void JudoMasterMainWindow::import()
{
    QString openFileName = QFileDialog::getOpenFileName(this, "Import CSV File", m_saveDir.absolutePath(), "CSV Files (*.csv)");

    if(openFileName.isEmpty())
    {
        return;
    }

    importFile(openFileName);
}

void JudoMasterMainWindow::loadFile(QString filename)
{
    QFile tournFile(filename);

    if(!tournFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file for reading");
        return;
    }

    QByteArray saveData = tournFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    m_tournament = new Tournament();
    m_tournament->setFileName(filename);


    QJsonObject jobj = loadDoc.object();
    m_tournament->read(jobj);

    JMApp()->clubController()->setTournament(m_tournament);
    JMApp()->competitorController()->setTournament(m_tournament);
    JMApp()->bracketController()->setTournament(m_tournament);


}

void JudoMasterMainWindow::importFile(QString filename)
{
    QFile file(filename);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream fileStream(&file);
        QString line = fileStream.readLine();
        QStringList headers = line.split(',');

        qDebug() << "Printing CSV Headers";
        QHash<QString, int> colMap;
        int index = 0;
        foreach(QString header, headers)
        {
            colMap[header] = index;
//            qDebug() << "Column: " << header << " Has index " << index;
            index++;
        }

        do
        {
            line = fileStream.readLine();
            if(!line.isNull())
            {
                QStringList columns = line.split(',');
                QString lname = columns.at(colMap["Last Name"]);
                QString fname = columns.at(colMap["First Name"]);
                QString gender = columns.at(colMap["Gender"]);
                QString age = columns.at(colMap["Age"]);
                QString weight = columns.at(colMap["Weight (Lbs)"]);
                QString belt = columns.at(colMap["Belt color / rank"]);
                QString clubName = columns.at(colMap["Club Name"]);
                QString div0 = columns.at(colMap["Division"]);
                QString div1 = columns.at(colMap["Division 1"]);
                QString div2 = columns.at(colMap["Division 2"]);
                QString div3 = columns.at(colMap["Division 3"]);

                int numDivs = 0;

                numDivs += div0.isEmpty() ? 0 : 1;
                numDivs += div1.isEmpty() ? 0 : 1;
                numDivs += div2.isEmpty() ? 0 : 1;
                numDivs += div3.isEmpty() ? 0 : 1;

                QString notes = QString("div0: (%1), div1: (%2), div2: (%3), div3: (%4)").arg(div0).arg(div1).arg(div2).arg(div3);
//                qDebug() << "First: " << fname << ", Last: " << lname << ", Gender: " << gender << ", Age: " << age << ", Weight: " << weight
//                         << ", belt: " << belt << ", club: " << clubName << ", num Divs: " << numDivs;

                // Let's find the club.
                Club *club = JMApp()->clubController()->findClubByName(clubName);
                if(club)
                {
                    // Found the Club
                    qDebug() << "Found Club '" << clubName << "' as '" << club->clubName() << "'";
                }
                else
                {
                    qDebug() << "Creating New Club for name " << clubName;
                    // Need to add the club.
                    club = JMApp()->clubController()->createClub();
                    club->setClubName(clubName);
                }

                // Now add the competitor.
                JM::Rank rank = rankFromString(belt);
                if(rank == JM::Unknown)
                {
                    notes += QString("belt: %1").arg(belt);
                }
                auto mf = genderFromString(gender);

                // See if the competitor is already added (from previous import)
                Competitor *competitor = JMApp()->competitorController()->findByName(fname, lname);

                if(!competitor)
                {
                    // Competitor not found, so add.
                    competitor = JMApp()->competitorController()->createCompetitor(fname,lname, mf, age.toInt(), weight.toDouble(), rank, club->id());
                    // TODO add the following to the constructor.
                    competitor->setNumBrackets(numDivs);
                    competitor->setNotes(notes);
                }

            }
        } while (!line.isNull());
        file.close();
    }

}

bool JudoMasterMainWindow::getFilename()
{
    QString newfileName = QFileDialog::getSaveFileName(this, "Save", m_saveDir.absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");
    if(newfileName.isEmpty())
    {
        return false;
    }

    QFileInfo finfo(newfileName);
    m_saveDir = finfo.absoluteDir();
    m_fileName = newfileName;

    m_tournament->setFileName(newfileName);
    return true;
}

void JudoMasterMainWindow::updateControls()
{
    bool enabled = m_tournament == 0 ? false : true;

    ui->detailsWidget->setEnabled(enabled);
    ui->tournamentName->setEnabled(enabled);
    ui->startTime->setEnabled(enabled);
    ui->tournamentDate->setEnabled(enabled);

    ui->actionSave->setEnabled(enabled);
    ui->actionSave_As->setEnabled(enabled);

    if(enabled)
    {
        ui->tournamentName->setText(m_tournament->name());
        ui->tournamentDate->setDate(m_tournament->date());
        ui->startTime->setTime(m_tournament->startTime());
    }
}
