#ifndef INGREDIENTLISTFORM_H
#define INGREDIENTLISTFORM_H

#include "FoodList/foodlistform.h"
#include "datastorage.h"

class IngredientListForm : public FoodListForm
{
public:
    explicit IngredientListForm(QWidget *parent = nullptr);

public slots:
    void onIngredientAddedToDB(std::shared_ptr<Food> newIngredient);
    void onIngredientRemovedFromDB(const QString &ingredientName);
    void onIngredientEditedInDB(const QString &oldIngredientName, std::shared_ptr<Food> newValue);

protected:
    virtual void setupUniqueSlots() override;

private:
    DataStorage &m_dataStorage;
};

#endif // INGREDIENTLISTFORM_H
