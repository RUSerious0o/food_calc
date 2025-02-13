#ifndef ALLFOODLISTFORM_H
#define ALLFOODLISTFORM_H

#include "FoodList/foodlistform.h"
#include "datastorage.h"

class AllFoodListForm : public FoodListForm
{
public:
    explicit AllFoodListForm(QWidget *parent = nullptr);

public slots:
    void onDishAddedToDB(std::shared_ptr<Food> newDish);
    void onDishRemovedFromDB(const QString &dishName);
    void onDishesEdited(std::map<QString, std::shared_ptr<Food>>);
    void onIngredientAddedToDB(std::shared_ptr<Food> newIngredient);
    void onIngredientRemovedFromDB(const QString &ingredientName);
    void onIngredientEditedInDB(const QString &oldIngredientName, std::shared_ptr<Food> newValue);

protected:
    virtual void setupUniqueSlots() override;

private:
    DataStorage &m_dataStorage;
};

#endif // ALLFOODLISTFORM_H
