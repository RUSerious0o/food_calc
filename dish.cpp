#include "dish.h"

Dish::Dish()
    : Food()
{
    calcPFC();
}

Dish::Dish(int id, const QString &name) :
    Food(id, name, 0, 0, 0),
    m_ingredients()
{
    calcPFC();
}

Dish::~Dish() {}

const std::map<QString, std::pair<std::shared_ptr<Food>, int> > Dish::ingredients() const
{
    return m_ingredients;
}

bool Dish::addOrEditIngredient(const std::shared_ptr<Food> ingredient, int amt)
{
    std::pair<std::shared_ptr<Food>, int> temp (new Food(ingredient->id(), ingredient->name(), ingredient->proteins(), ingredient->fats(), ingredient->carbohs()), amt);
    m_ingredients.insert_or_assign(ingredient->name(), temp);
    calcPFC();
    updateDescriptions();
    return true;
}

bool Dish::removeIngredient(const QString &ingredientName)
{
    m_ingredients[ingredientName].first.reset();
    m_ingredients.erase(ingredientName);
    calcPFC();
    return true;
}

void Dish::calcPFC()
{
    if(m_ingredients.size() == 0) {
        this->setProteins(0);
        this->setFats(0);
        this->setCarbohs(0);
        return;
    }

    int amtSum = 0;
    double proteinsSum = 0;
    double fatsSum = 0;
    double carbohsSum = 0;

    for(auto temp : m_ingredients) {
        int amt = temp.second.second;
        amtSum += amt;
        proteinsSum += temp.second.first->proteins() * amt / 100;
        fatsSum += temp.second.first->fats() * amt / 100;
        carbohsSum += temp.second.first->carbohs() * amt / 100;
    }

    if(amtSum == 0) {
        return;
    }

    double divider = 0.01 * amtSum;
    this->setProteins(floor(proteinsSum / divider * 10) / 10);
    this->setFats(floor(fatsSum / divider * 10) / 10);
    this->setCarbohs(floor(carbohsSum / divider * 10) / 10);
}
