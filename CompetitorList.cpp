#include "CompetitorList.h"
#include "ui_CompetitorList.h"

#include "CompetitorTableModel.h"
#include "JudoMasterApplication.h"

CompetitorList::CompetitorList(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::CompetitorList)
    , m_clubId(-1)
{
    ui->setupUi(this);

    CompetitorTableModel *model = new CompetitorTableModel(ui->competitorTable);

    ui->competitorTable->setModel(model);

    connect(ui->addBtn, &QPushButton::clicked, this, &CompetitorList::addCompetitor);
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
}

void CompetitorList::addCompetitor()
{
    JMApp()->competitorController()->createClubCompetitor(m_clubId);
}
