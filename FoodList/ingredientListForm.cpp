#include "ingredientListForm.h"

IngredientListForm::IngredientListForm(QWidget *parent) :
    FoodListForm(parent),
    m_dataStorage(DataStorage::getInstance())
{
    setupFoodList(m_dataStorage.ingredientsMap());
    setupUniqueSlots();
}

void IngredientListForm::onIngredientAddedToDB(std::shared_ptr<Food> newIngredient)
{
    addFood(newIngredient, 0);
}

void IngredientListForm::onIngredientRemovedFromDB(const QString &ingredientName)
{
    removeFood(ingredientName);
}

void IngredientListForm::onIngredientEditedInDB(const QString &oldIngredientName, std::shared_ptr<Food> newValue)
{
    removeFood(oldIngredientName);
    addFood(newValue, 0);
}

void IngredientListForm::setupUniqueSlots()
{
    connect(&m_dataStorage, &DataStorage::ingredientAdded, this, &IngredientListForm::onIngredientAddedToDB);
    connect(&m_dataStorage, &DataStorage::ingredientRemoved, this, &IngredientListForm::onIngredientRemovedFromDB);
    connect(&m_dataStorage, &DataStorage::ingredientEdited, this, &IngredientListForm::onIngredientEditedInDB);
}
