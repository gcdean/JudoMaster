#include "BracketCompetitorTableModel.h"

BracketCompetitorTableModel::BracketCompetitorTableModel(BaseController *controller, QObject *parent)
    : CompetitorTableModel(controller, parent)
{

}

BracketCompetitorTableModel::~BracketCompetitorTableModel()
{

}

QStringList BracketCompetitorTableModel::mimeTypes() const
{
    return CompetitorTableModel::mimeTypes();
}

bool BracketCompetitorTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    return CompetitorTableModel::dropMimeData(data, action, row, column, parent);
}

