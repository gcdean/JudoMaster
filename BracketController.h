#ifndef BRACKETCONTROLLER_H
#define BRACKETCONTROLLER_H

#include "BaseController.h"
#include <QObject>

class BracketController : public BaseController
{
    Q_OBJECT

public:
    BracketController(QObject *parent = 0);

    // Overrides
    int size() const override;
    int size(int id) const override;

    void add(int parentId) override;
    void remove(int id) override;

private:
    int findNextId() override;
};

#endif // BRACKETCONTROLLER_H
