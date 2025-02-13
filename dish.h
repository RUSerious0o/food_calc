#ifndef DISH_H
#define DISH_H

#include "food.h"

#include <QObject>

#include <map>
#include <cmath>
#include <memory>

class Dish : public Food
{
    Q_OBJECT
public:
    Dish();
    Dish(int id, const QString& name);
    ~Dish();

    const std::map<QString, std::pair<std::shared_ptr<Food>, int>> ingredients() const;
    bool addOrEditIngredient(const std::shared_ptr<Food>, int);
    bool removeIngredient(const QString &ingredientName);

private:
    std::map<QString, std::pair<std::shared_ptr<Food>, int>> m_ingredients;

    void calcPFC();
};

#endif // DISH_H
