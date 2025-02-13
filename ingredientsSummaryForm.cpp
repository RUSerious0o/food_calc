#include "ingredientsSummaryForm.h"
#include "ui_ingredientsSummaryForm.h"

IngredientsSummaryForm::IngredientsSummaryForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IngredientsSummaryForm),
    m_dataStorage(DataStorage::getInstance()),
    foodListWidget(new IngredientListForm(this)),
    ingredientInputForm(),
    doubleValidator(new QDoubleValidator(0.0, 100.0, 1, this)),
    m_mode(AddIngredient),
    editedFood(nullptr)
{
    ui->setupUi(this);
    collectIngredientInputWidgets();
    hideIngredientInputWidgets();

    ui->verticalLayout->insertWidget(-1, foodListWidget);

    setupSlots();

    ui->proteinsInput->setValidator(doubleValidator);
    ui->fatsInput->setValidator(doubleValidator);
    ui->carbohsInput->setValidator(doubleValidator);
}

IngredientsSummaryForm::~IngredientsSummaryForm()
{
    delete ui;
}

void IngredientsSummaryForm::onAddIngredientButtonClicked()
{
    showIngredientInputWidgets();
    m_mode = AddIngredient;
    fillIngredientInputWidgetFields(std::shared_ptr<Food> (new Food()));

    editedFood.reset();
}

void IngredientsSummaryForm::onIngredientListItemClicked(const std::shared_ptr<Food> food)
{
    showIngredientInputWidgets();
    m_mode = EditIngredient;
    fillIngredientInputWidgetFields(food);

    editedFood = std::shared_ptr<Food> (new Food(food->id(), food->name(), food->proteins(), food->fats(), food->carbohs()));
}

void IngredientsSummaryForm::onIngredientInfoCommited()
{
    auto ingredientName = ui->ingredientNameInput->text();
    if(ingredientName == "") {
        return;
    }

    double proteins = ui->proteinsInput->text().replace(',','.').toDouble();
    double fats = ui->fatsInput->text().replace(',','.').toDouble();
    double carbohs = ui->carbohsInput->text().replace(',','.').toDouble();

    if(m_mode == AddIngredient) {
        if(!m_dataStorage.addIngredient(ingredientName, proteins, fats, carbohs)) {
            qDebug() << "New ingredient addition failed!";
            return;
        }
    }

    if(m_mode == EditIngredient) {
        if(!editedFood) {
            return;
        }

        if(!m_dataStorage.editIngredient(editedFood->id(), editedFood->name(), ingredientName, proteins, fats, carbohs)) {
            qDebug() << "Ingredient edittion failed!";
        }
    }

    hideIngredientInputWidgets();
}

void IngredientsSummaryForm::fixupPFCInput()
{
    double inputValue = ui->proteinsInput->text().replace(',','.').toDouble();
    if(inputValue > 100) {
        ui->proteinsInput->setText(QString("%1").arg(inputValue/10));
    }

    inputValue = ui->fatsInput->text().replace(',','.').toDouble();
    if(inputValue > 100) {
        ui->fatsInput->setText(QString("%1").arg(inputValue/10));
    }

    inputValue = ui->carbohsInput->text().replace(',','.').toDouble();
    if(inputValue > 100) {
        ui->carbohsInput->setText(QString("%1").arg(inputValue/10));
    }
}

void IngredientsSummaryForm::onDeleteIngredientCommited()
{
    if(m_mode != EditIngredient || !editedFood) {
        return;
    }

    m_dataStorage.removeIngredient(editedFood->id(), editedFood->name());
    onAddIngredientButtonClicked();
}

void IngredientsSummaryForm::collectIngredientInputWidgets()
{
    ingredientInputForm.push_back(ui->ingredientNameInput);
    ingredientInputForm.push_back(ui->proteinsInput);
    ingredientInputForm.push_back(ui->fatsInput);
    ingredientInputForm.push_back(ui->carbohsInput);
    ingredientInputForm.push_back(ui->ingredientCommitButton);
    ingredientInputForm.push_back(ui->proteinsLabel);
    ingredientInputForm.push_back(ui->fatsLabel);
    ingredientInputForm.push_back(ui->carbohsLabel);
    ingredientInputForm.push_back(ui->deleteIngredientButton);
}

void IngredientsSummaryForm::hideIngredientInputWidgets()
{
    for(auto widget : ingredientInputForm) {
        widget->hide();
    }
}

void IngredientsSummaryForm::showIngredientInputWidgets()
{
    for(auto widget : ingredientInputForm) {
        widget->show();
    }
}

void IngredientsSummaryForm::setupSlots()
{
    connect(ui->addIngredientButton, &QPushButton::clicked, this, &IngredientsSummaryForm::onAddIngredientButtonClicked);    
    connect(ui->ingredientCommitButton, &QPushButton::clicked, this, &IngredientsSummaryForm::onIngredientInfoCommited);
    connect(ui->proteinsInput, &QLineEdit::textChanged, this, &IngredientsSummaryForm::fixupPFCInput);
    connect(ui->fatsInput, &QLineEdit::textChanged, this, &IngredientsSummaryForm::fixupPFCInput);
    connect(ui->carbohsInput, &QLineEdit::textChanged, this, &IngredientsSummaryForm::fixupPFCInput);
    connect(ui->deleteIngredientButton, &QPushButton::clicked, this, &IngredientsSummaryForm::onDeleteIngredientCommited);

    connect(foodListWidget, &FoodListForm::itemClicked, this, &IngredientsSummaryForm::onIngredientListItemClicked);
}

void IngredientsSummaryForm::fillIngredientInputWidgetFields(const std::shared_ptr<Food> food)
{
    ui->ingredientNameInput->setText(food->name());
    ui->proteinsInput->setText(QString("%1").arg(food->proteins()));
    ui->fatsInput->setText(QString("%1").arg(food->fats()));
    ui->carbohsInput->setText(QString("%1").arg(food->carbohs()));        
}
