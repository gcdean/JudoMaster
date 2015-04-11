#include "JMDataObj.h"

#include <QJsonObject>
#include <QTextStream>

JMDataObj::JMDataObj(int id)
    : m_id(id)
{
}

JMDataObj::JMDataObj(const JMDataObj& src)
{
    m_id = src.id();
}

JMDataObj::JMDataObj(const QJsonObject &json)
{
    read(json);
}

int JMDataObj::id() const
{
    return m_id;
}

void JMDataObj::read(const QJsonObject &json)
{
    m_id = json["id"].toInt();
}

void JMDataObj::write(QJsonObject &json) const
{
    json["id"] = m_id;
}

void JMDataObj::write(QTextStream &stream) const
{
    stream << m_id;
}
