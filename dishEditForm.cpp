#include "dishEditForm.h"
#include "ui_dishEditForm.h"

DishEditForm::DishEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishEditForm),
    m_dataStorage(DataStorage::getInstance()),
    ingredientsListWidget(new IngredientListForm(this)),
    m_mode(DishAddMode),
    currentDish(nullptr),
    selectedIngredient(nullptr)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(-1, ingredientsListWidget);
    ui->verticalLayout->insertStretch(-1,1);
    ui->ingredientWeightInput->setValidator(new QIntValidator(this));

    connectSlots();        
}

DishEditForm::~DishEditForm()
{
    delete ui;    
}

void DishEditForm::setupDish(const QString &dishName)
{
    m_mode = dishName == "" ? DishAddMode : DishEditMode;
    setupViewsVisibility();
    ui->dishNameInput->setText(dishName);

    if(currentDish != nullptr) {
        currentDish = nullptr;
    }

    if(dishName != "") {
        int dishId = m_dataStorage.getFoodId(dishName, DataStorage::FoodType::DishType);
        currentDish.reset(new Dish(dishId, dishName));
        auto dishIngredients = m_dataStorage.dishIngredients(dishId);
        if(dishIngredients.size() > 0) {
            for(auto ingredient : dishIngredients) {
                currentDish->addOrEditIngredient(ingredient.second.first, ingredient.second.second);
            }
        }
    }

    refreshIngredientWidgets();
}

void DishEditForm::onDishNameEditCommited()
{
    auto dishName = ui->dishNameInput->text();
    if(dishName == "") {
        return;
    }

    if(currentDish == nullptr) {
        m_mode = DishEditMode;
        if(m_dataStorage.addFoodName(dishName, DataStorage::FoodType::DishType)) {
            currentDish.reset(new Dish(m_dataStorage.getFoodId(dishName, DataStorage::FoodType::DishType), dishName));
            setupViewsVisibility();
        } else {
            qDebug() << "Что-то пошло не так. Возможно, блюдо уже существует";
        }
    } else {
        qDebug() << currentDish->id() << " " << currentDish->name();
        if(!m_dataStorage.editFoodName(currentDish->id(), currentDish->name(), dishName, DataStorage::FoodType::DishType)) {
            ui->dishNameInput->setText(currentDish->name());
        };
    }
}

void DishEditForm::onIngredientSelected(const std::shared_ptr<Food> ingredient)
{
    ui->selectedIngredientLabel->setText(ingredient->name());
    ui->ingredientWeightInput->setFocus();
    ui->ingredientWeightInput->setSelection(0, ui->ingredientWeightInput->maxLength());

    selectedIngredient.reset(new Food(ingredient->id(), ingredient->name(), ingredient->proteins(), ingredient->fats(), ingredient->carbohs()));
}

void DishEditForm::onIngredientCommitClicked()
{
    int ingredientWeight = ui->ingredientWeightInput->text().toInt();
    if(ingredientWeight == 0 || ui->selectedIngredientLabel->text() == DEFAULT_NEW_INREDIENT_LABEL_TEXT) {
        return;
    }

    currentDish->addOrEditIngredient(selectedIngredient, ingredientWeight);
    m_dataStorage.setDishIngredient(currentDish->id(), selectedIngredient->id(), ingredientWeight);
    refreshIngredientWidgets();
}

void DishEditForm::onDeleteDishButtonClicked()
{
    if(m_dataStorage.removeDish(currentDish->id(), currentDish->name())) {
        currentDish = nullptr;
        m_mode = DishAddMode;
        setupViewsVisibility();
        refreshIngredientWidgets();
    }
}

void DishEditForm::onDishIngredientDeleteButtonClicked()
{
    if(!selectedIngredient) {
        return;
    }

    m_dataStorage.removeDishIngredient(currentDish->id(), selectedIngredient->id());
    currentDish->removeIngredient(selectedIngredient->name());
    selectedIngredient = nullptr;
    refreshIngredientWidgets();
}

void DishEditForm::setupViewsVisibility()
{    
    std::list<QHBoxLayout*> editDishLayouts {
                ui->horizontalLayout_3,
                ui->horizontalLayout_4,
                ui->ingredientsLayout
    };

    if(m_mode == DishAddMode) {
        for(auto layout : editDishLayouts) {
            for(int i = 0; i < layout->count(); ++i) {
                layout->itemAt(i)->widget()->hide();
            }
        }

        ui->deleteDishButton->hide();
        ingredientsListWidget->hide();

    } else if (m_mode == DishEditMode) {
        for(auto layout : editDishLayouts) {
            for(int i = 0; i < layout->count(); ++i) {
                layout->itemAt(i)->widget()->show();
            }
        }

        ui->deleteDishButton->show();
        ingredientsListWidget->show();
    }
}

void DishEditForm::connectSlots()
{
    connect(ui->dishNameCommitButton, &QPushButton::clicked, this, &DishEditForm::onDishNameEditCommited);
    connect(ingredientsListWidget, &FoodListForm::itemClicked, this, &DishEditForm::onIngredientSelected);
    connect(ui->ingredientCommitButton, &QPushButton::clicked, this, &DishEditForm::onIngredientCommitClicked);
    connect(ui->deleteDishButton, &QPushButton::clicked, this, &DishEditForm::onDeleteDishButtonClicked);
    connect(ui->dishIngredientDeleteButton, &QPushButton::clicked, this, &DishEditForm::onDishIngredientDeleteButtonClicked);
}

void DishEditForm::refreshIngredientWidgets()
{
    ui->proteinsLabel->setText("0");
    ui->fatsLabel->setText("0");
    ui->carbohsLabel->setText("0");
    ui->caloriesLabel->setText("0");

    if(ui->dishIngredientsLayout->count() > 0) {
        for(int i = ui->dishIngredientsLayout->count() - 1; i >= 0; --i) {
            auto temp = ui->dishIngredientsLayout->takeAt(i)->widget();
            temp->hide();
            delete temp;
        }        
    }

    if(selectedIngredient == nullptr) {
        ui->selectedIngredientLabel->setText(DEFAULT_NEW_INREDIENT_LABEL_TEXT);
    }

    if(!currentDish) {
        return;
    }

    for(auto ingredient : currentDish->ingredients()) {
        auto ingredientWidget = new DishIngredientsListItemForm(ingredient.second.first, ingredient.second.second, this);
        ui->dishIngredientsLayout->addWidget(ingredientWidget);
        connect(ingredientWidget, &DishIngredientsListItemForm::itemClicked, this, &DishEditForm::onIngredientSelected);
    }

    ui->proteinsLabel->setText(QString("%1").arg(currentDish->proteins()));
    ui->fatsLabel->setText(QString("%1").arg(currentDish->fats()));
    ui->carbohsLabel->setText(QString("%1").arg(currentDish->carbohs()));
    ui->caloriesLabel->setText(QString("%1").arg(currentDish->calories()));
}
