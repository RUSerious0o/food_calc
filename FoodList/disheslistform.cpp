#include "dishesListForm.h"

DishesListForm::DishesListForm(QWidget *parent)
    : FoodListForm(parent)
    , m_dataStorage(DataStorage::getInstance())
{
    setupFoodList(m_dataStorage.dishesMap());
    setupUniqueSlots();
}

void DishesListForm::onDishAddedToDB(std::shared_ptr<Food> newDish)
{
    addFood(newDish, 0);
}

void DishesListForm::onDishRemovedFromDB(const QString &dishName)
{
    removeFood(dishName);
}

void DishesListForm::onDishesEdited(std::map<QString, std::shared_ptr<Food> > editedDishes)
{
    for(auto dish : editedDishes) {
        removeFood(foodName(dish.second->id()));
        addFood(dish.second, 0);
    }
}

void DishesListForm::setupUniqueSlots()
{
    connect(&m_dataStorage, &DataStorage::dishAdded, this, &DishesListForm::onDishAddedToDB);
    connect(&m_dataStorage, &DataStorage::dishRemoved, this, &DishesListForm::onDishRemovedFromDB);
    connect(&m_dataStorage, &DataStorage::dishesEdited, this, &DishesListForm::onDishesEdited);
}

