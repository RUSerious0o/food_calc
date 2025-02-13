#include "food.h"

Food::Food() :
    m_id(0),
    m_name(""),
    m_proteins(0),
    m_fats(0),
    m_carbohs(0),    
    m_viewedDescription(""),
    m_codedDescription("")
{

}

Food::Food(const QByteArray &data) : Food()
{
    auto splittedData = data.split('|');
    m_id = splittedData[0].toInt();
    m_name = splittedData[1];
    m_proteins = splittedData[3].toDouble();
    m_fats = splittedData[4].toDouble();
    m_carbohs= splittedData[5].toDouble();

    updateDescriptions();
}

Food::Food(int id, const QString &name, double proteins, double fats, double carbohs)
    : m_id(id)
    , m_name(name)
    , m_proteins(proteins)
    , m_fats(fats)
    , m_carbohs(carbohs)
{
    updateDescriptions();
}

int Food::id() const
{
    return m_id;
}

const QString &Food::name() const
{
    return m_name;
}

double Food::proteins() const
{
    return m_proteins;
}

double Food::fats() const
{
    return m_fats;
}

double Food::carbohs() const
{
    return m_carbohs;
}

double Food::calories() const
{
    return m_proteins * 4.1 + m_fats * 9.3 + m_carbohs * 4.1;
}

const QString &Food::viewedDescription() const
{
    return m_viewedDescription;
}


const QString &Food::codedDescription() const
{
    return m_codedDescription;
}

void Food::setId(int id)
{
    m_id = id;
    setCodedDescription();
}

void Food::setName(const QString &name)
{
    m_name = name;
}

void Food::setProteins(double proteins)
{
    m_proteins = proteins;
}

void Food::setFats(double fats)
{
    m_fats = fats;
}

void Food::setCarbohs(double carbohs)
{
    m_carbohs = carbohs;
}

void Food::updateDescriptions()
{
    setViewedlDescription();
    setCodedDescription();
}

void Food::setViewedlDescription()
{
    m_viewedDescription = QString("%1 Б: %2 Ж: %3 У: %4 Ккал: %5 / 100 г")
            .arg(m_name)
            .arg(m_proteins)
            .arg(m_fats)
            .arg(m_carbohs)
            .arg(calories());
}

void Food::setCodedDescription()
{
    m_codedDescription = QString("%1|%2|БЖУ|%3|%4|%5")
            .arg(m_id)
            .arg(m_name)
            .arg(m_proteins)
            .arg(m_fats)
            .arg(m_carbohs);
}
