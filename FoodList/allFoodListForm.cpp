#include "allFoodListForm.h"

AllFoodListForm::AllFoodListForm(QWidget *parent)
    : FoodListForm(parent)
    , m_dataStorage(DataStorage::getInstance())
{
    setupFoodList(m_dataStorage.fullFoodMap());
    setupUniqueSlots();
}

void AllFoodListForm::setupUniqueSlots()
{
    connect(&m_dataStorage, &DataStorage::dishAdded, this, &AllFoodListForm::onDishAddedToDB);
    connect(&m_dataStorage, &DataStorage::dishRemoved, this, &AllFoodListForm::onDishRemovedFromDB);
    connect(&m_dataStorage, &DataStorage::dishesEdited, this, &AllFoodListForm::onDishesEdited);
    connect(&m_dataStorage, &DataStorage::ingredientAdded, this, &AllFoodListForm::onIngredientAddedToDB);
    connect(&m_dataStorage, &DataStorage::ingredientRemoved, this, &AllFoodListForm::onIngredientRemovedFromDB);
    connect(&m_dataStorage, &DataStorage::ingredientEdited, this, &AllFoodListForm::onIngredientEditedInDB);
}

void AllFoodListForm::onDishAddedToDB(std::shared_ptr<Food> newDish)
{
    addFood(newDish, 0);
}

void AllFoodListForm::onDishRemovedFromDB(const QString &dishName)
{
    removeFood(dishName);
}

void AllFoodListForm::onDishesEdited(std::map<QString, std::shared_ptr<Food> > editedDishes)
{
    for(auto dish : editedDishes) {
        removeFood(foodName(dish.second->id()));
        addFood(dish.second, 0);
    }
}

void AllFoodListForm::onIngredientAddedToDB(std::shared_ptr<Food> newIngredient)
{
    addFood(newIngredient, 0);
}

void AllFoodListForm::onIngredientRemovedFromDB(const QString &ingredientName)
{
    removeFood(ingredientName);
}

void AllFoodListForm::onIngredientEditedInDB(const QString &oldIngredientName, std::shared_ptr<Food> newValue)
{
    removeFood(oldIngredientName);
    addFood(newValue, 0);
}
