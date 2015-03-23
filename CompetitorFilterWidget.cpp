#include "CompetitorFilterWidget.h"
#include "ui_CompetitorFilterWidget.h"

#include <QPushButton>

CompetitorFilterWidget::CompetitorFilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompetitorFilterWidget)
{
    ui->setupUi(this);

    connect(ui->applyBtn, &QPushButton::clicked, this, &CompetitorFilterWidget::apply);
    connect(ui->clearBtn, &QPushButton::clicked, this, &CompetitorFilterWidget::clearFilters);
}

CompetitorFilterWidget::~CompetitorFilterWidget()
{
    delete ui;
}

void CompetitorFilterWidget::clearFilters()
{
    ui->minAge->setValue(0);
    ui->maxAge->setValue(0);
    ui->minWt->setValue(0);
    ui->maxWt->setValue(0);
    ui->lastName->setText(QString());
    ui->maleChkBox->setChecked(false);
    ui->femaleChkBox->setChecked(false);
}

void CompetitorFilterWidget::apply()
{
    emit applyFilter(CompetitorFilter(ui->minAge->value(), ui->maxAge->value(), ui->minWt->value(), ui->maxWt->value(), ui->lastName->text(), ui->maleChkBox->isChecked(), ui->femaleChkBox->isChecked()));
}
