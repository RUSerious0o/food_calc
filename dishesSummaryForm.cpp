#include "dishesSummaryForm.h"

DishesSummaryForm::DishesSummaryForm(QWidget *parent)
    : QWidget(parent)
    , m_dataStorage(DataStorage::getInstance())
    , mainLayout(new QVBoxLayout(this))
    , addDishButton(new QPushButton(this))
    , dishesList(new DishesListForm(this))
    , dishEditWidget(new DishEditForm(this))

{
    this->setLayout(mainLayout);
    addDishButton->setText(tr(ADD_DISH_BUTTON_TEXT));

    mainLayout->addWidget(addDishButton);
    mainLayout->addWidget(dishesList);

    mainLayout->insertWidget(0, dishEditWidget);
    dishEditWidget->hide();

    setupSlots();
}

void DishesSummaryForm::refresh()
{
    hideDishEditForm();
}

void DishesSummaryForm::onAddDishButtonClicked()
{
    showDishEditForm();
    dishEditWidget->setupDish();
}

void DishesSummaryForm::onDishSelected(const std::shared_ptr<Food> selectedDish)
{
    showDishEditForm();
    dishEditWidget->setupDish(selectedDish->name());
}

void DishesSummaryForm::showDishEditForm()
{
    dishEditWidget->show();
    dishesList->hide();
    addDishButton->hide();
}

void DishesSummaryForm::hideDishEditForm()
{
    dishEditWidget->hide();
    dishesList->show();
    addDishButton->show();
}

void DishesSummaryForm::setupSlots()
{
    connect(addDishButton, &QPushButton::clicked, this, &DishesSummaryForm::onAddDishButtonClicked);
    connect(dishesList, &FoodListForm::itemClicked, this, &DishesSummaryForm::onDishSelected);
}
