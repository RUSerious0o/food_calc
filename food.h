#ifndef FOOD_H
#define FOOD_H

#include <QByteArray>
#include <QObject>
#include <QString>

class Food : public QObject
{
    Q_OBJECT
public:
    Food();
    Food(const QByteArray&);
    Food(int id, const QString& name, double proteins, double fats, double carbohs);

    int id() const;
    const QString& name() const;
    double proteins() const;
    double fats() const;
    double carbohs() const;
    double calories() const;

    const QString& viewedDescription() const;
    const QString& codedDescription() const;

    void setId(int id);
    void setName(const QString&);
    void setProteins(double proteins);
    void setFats(double fats);
    void setCarbohs(double carbohs);

    void updateDescriptions();
private:
    int m_id;
    QString m_name;
    double m_proteins;
    double m_fats;
    double m_carbohs;

    QString m_viewedDescription;
    QString m_codedDescription;

    void setViewedlDescription();
    void setCodedDescription();
};

#endif // FOOD_H
