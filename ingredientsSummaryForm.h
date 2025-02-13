#ifndef INGREDIENTSSUMMARYFORM_H
#define INGREDIENTSSUMMARYFORM_H

#include <QDoubleValidator>
#include <QWidget>

#include <vector>
#include <memory>

#include "datastorage.h"
#include "FoodList/ingredientListForm.h"

namespace Ui {
class IngredientsSummaryForm;
}

class IngredientsSummaryForm : public QWidget
{
    Q_OBJECT

public:
    explicit IngredientsSummaryForm(QWidget *parent = nullptr);
    ~IngredientsSummaryForm();

public slots:
    void onAddIngredientButtonClicked();
    void onIngredientListItemClicked(const std::shared_ptr<Food>);
    void onIngredientInfoCommited();
    void fixupPFCInput();
    void onDeleteIngredientCommited();

private:
    enum Mode {
        AddIngredient,
        EditIngredient
    };

    Ui::IngredientsSummaryForm *ui;
    DataStorage &m_dataStorage;
    FoodListForm *foodListWidget;
    std::vector<QWidget*> ingredientInputForm;
    QDoubleValidator *doubleValidator;
    Mode m_mode;
    std::shared_ptr<Food> editedFood;

    void collectIngredientInputWidgets();
    void hideIngredientInputWidgets();
    void showIngredientInputWidgets();

    void setupSlots();

    void fillIngredientInputWidgetFields(const std::shared_ptr<Food>);


};

#endif // INGREDIENTSSUMMARYFORM_H
