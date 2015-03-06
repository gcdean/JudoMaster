#ifndef BRACKETCOMPETITORTABLEMODEL_H
#define BRACKETCOMPETITORTABLEMODEL_H

#include "CompetitorTableModel.h"

class BracketCompetitorTableModel : public CompetitorTableModel
{
public:
    BracketCompetitorTableModel(BaseController* controller, QObject *parent = 0);
    ~BracketCompetitorTableModel();

    // QAbstractItemModel interface
public:
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

};

#endif // BRACKETCOMPETITORTABLEMODEL_H
