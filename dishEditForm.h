#ifndef DISHEDITFORM_H
#define DISHEDITFORM_H

#include <QWidget>
#include <QIntValidator>

#include <list>
#include <memory>


#include "datastorage.h"
#include "dish.h"
#include "dishIngredientsListItemForm.h"
#include "FoodList/ingredientListForm.h"

namespace Ui {
class DishEditForm;
}

class DishEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit DishEditForm(QWidget *parent = nullptr);
    ~DishEditForm();

    void setupDish(const QString &name = "");

public slots:
    void onDishNameEditCommited();
    void onIngredientSelected(const std::shared_ptr<Food> ingredient);
    void onIngredientCommitClicked();
    void onDeleteDishButtonClicked();
    void onDishIngredientDeleteButtonClicked();

private:
    enum Mode {
        DishAddMode,
        DishEditMode
    };

    Ui::DishEditForm *ui;
    DataStorage &m_dataStorage;
    FoodListForm *ingredientsListWidget;
    Mode m_mode;
    std::shared_ptr<Dish> currentDish;
    std::shared_ptr<Food> selectedIngredient;

    const QString DEFAULT_NEW_INREDIENT_LABEL_TEXT = "Выберите ингредиент";

    void setupViewsVisibility();
    void connectSlots();
    void refreshIngredientWidgets();
};

#endif // DISHEDITFORM_H
