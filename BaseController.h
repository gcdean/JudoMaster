#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QObject>

class Tournament;
class JMDataObj;

class BaseController : public QObject
{
    Q_OBJECT
public:
    explicit BaseController(QObject *parent = 0);
    void setTournament(Tournament* tournament);

    virtual int size() const;    // Size of all elements in the list
    virtual int size(int id) const;  // Size of all elements with given id or parent with id.

    virtual void add(int parentId); // Creates and adds a new object to the model
    virtual void remove(int id);    // Remove the object with the specified id

signals:
    void tournamentChanged();
    void addedDataObj(JMDataObj *obj);

public slots:

protected:
    Tournament* tournament() const;
    virtual int findNextId() = 0;

private:
    Tournament* m_tournament;
};

#endif // BASECONTROLLER_H