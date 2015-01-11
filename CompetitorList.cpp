#include "CompetitorList.h"
#include "ui_CompetitorList.h"

#include "ClubController.h"
#include "CompetitorTableModel.h"
#include "JudoMasterApplication.h"

#include <QAbstractTableModel>

CompetitorList::CompetitorList(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::CompetitorList)
    , m_clubId(-1)
    , m_controller(0)
{
    ui->setupUi(this);

    connect(ui->addBtn, &QPushButton::clicked, this, &CompetitorList::add);
    connect(JMApp()->clubController(), &ClubController::tournamentChanged, this, &CompetitorList::tournamentChanged);
}

CompetitorList::~CompetitorList()
{
    delete ui;
}

void CompetitorList::setClubId(int id)
{
    m_clubId = id;
    CompetitorTableModel *model = dynamic_cast<CompetitorTableModel *>(ui->competitorTable->model());

    model->setClubId(id);
    ui->competitorTable->reset();
}

void CompetitorList::setModel(QAbstractTableModel *model)
{
    model->setParent(ui->competitorTable);
    ui->competitorTable->setModel(model);
}

void CompetitorList::setController(BaseController *controller)
{
    m_controller = controller;
}

void CompetitorList::add()
{
    if(m_controller)
    {
        m_controller->add(m_clubId);
    }
}

void CompetitorList::remove()
{
    // Remove Selected items.
}

void CompetitorList::tournamentChanged()
{
    ui->competitorTable->reset();
}
