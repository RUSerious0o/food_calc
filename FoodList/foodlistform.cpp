#include "foodlistform.h"
#include "ui_foodlistform.h"

FoodListForm::FoodListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FoodListForm),
    m_foodList(),
    m_foodInfoWidgets()
{
    ui->setupUi(this);
    setupSlots();
}

FoodListForm::~FoodListForm()
{
    delete ui;
}

void FoodListForm::onIngredientFilterAdded(const QString &filter)
{
    if(filter.size() == 0) {
        onRemoveFilterRequested();
        return;
    }

    if(filter.size() < 3) return;

    ProductsListItem *firstShownWidget = nullptr;
    for(auto widget : m_foodInfoWidgets) {
        if(widget.first.toLower().contains(filter.toLower())) {            
            widget.second->show();
            if(firstShownWidget == nullptr) {
                firstShownWidget = widget.second;
                emit itemClicked(widget.second->food());
                ui->foodFilterlineEdit->setFocus();
            }
        } else {
            widget.second->hide();
        }
    }
}

void FoodListForm::onSortByPFCClicked()
{
    std::multimap<double, ProductsListItem*> widgets;
    for(auto widget : m_foodInfoWidgets) {
        widget.second->hide();
    }

    for(int i = ui->verticalLayout_2->count() - 1; i >= 0; --i) {
        ProductsListItem *temp = dynamic_cast<ProductsListItem*>(ui->verticalLayout_2->takeAt(i)->widget());
        if(dynamic_cast<QPushButton*>(sender())->objectName() == "sortByPbutton") {
            widgets.insert(std::pair(temp->food()->proteins(), temp));
        } else if(dynamic_cast<QPushButton*>(sender())->objectName() == "sortByFbutton") {
            widgets.insert(std::pair(temp->food()->fats(), temp));
        } else if(dynamic_cast<QPushButton*>(sender())->objectName() == "sortByCHbutton") {
            widgets.insert(std::pair(temp->food()->carbohs(), temp));
        } else if(dynamic_cast<QPushButton*>(sender())->objectName() == "sortByCalButton") {
            widgets.insert(std::pair(temp->food()->calories(), temp));
        }
    }

    for(auto widget : widgets) {
        ui->verticalLayout_2->insertWidget(0, widget.second);
        widget.second->show();
    }
}

void FoodListForm::onSortByNameClicked()
{
    for(auto widget : m_foodInfoWidgets) {
        widget.second->hide();
    }

    for(int i = ui->verticalLayout_2->count() - 1; i >= 0; --i) {
        ui->verticalLayout_2->takeAt(i)->widget();
    }

    for(auto widget : m_foodInfoWidgets) {
        ui->verticalLayout_2->addWidget(widget.second);
        widget.second->show();
    }
}

void FoodListForm::setupFoodListWidgets()
{
    for(auto food : m_foodList) {
        addFoodWidget(food.second);
    }
}

void FoodListForm::setupSlots()
{
    connect(ui->foodFilterlineEdit, &QLineEdit::textChanged, this, &FoodListForm::onIngredientFilterAdded);

    connect(ui->sortByPbutton, &QPushButton::clicked, this, &FoodListForm::onSortByPFCClicked);
    connect(ui->sortByFbutton, &QPushButton::clicked, this, &FoodListForm::onSortByPFCClicked);
    connect(ui->sortByCHbutton, &QPushButton::clicked, this, &FoodListForm::onSortByPFCClicked);
    connect(ui->sortByCalButton, &QPushButton::clicked, this, &FoodListForm::onSortByPFCClicked);
    connect(ui->sortByNameButton, &QPushButton::clicked, this, &FoodListForm::onSortByNameClicked);  
}

void FoodListForm::addFood(std::shared_ptr<Food> newFood, int index)
{
    if(m_foodList.find(newFood->name()) == m_foodList.end()) {
        m_foodList[newFood->name()] = newFood;
        addFoodWidget(newFood, index);
    }
}

void FoodListForm::addFoodWidget(std::shared_ptr<Food> food, int index)
{
    m_foodInfoWidgets[food->name()] = new ProductsListItem(food, this);
    ui->verticalLayout_2->insertWidget(index, m_foodInfoWidgets[food->name()]);
    connect(m_foodInfoWidgets[food->name()], SIGNAL(clicked(const std::shared_ptr<Food>)), this, SIGNAL(itemClicked(const std::shared_ptr<Food>)));
}

void FoodListForm::removeFood(const QString &foodName)
{
    if(m_foodList.find(foodName) != m_foodList.end()) {
        m_foodInfoWidgets[foodName]->hide();
        m_foodInfoWidgets.erase(foodName);
        m_foodList.erase(foodName);
    }
}

const QString FoodListForm::foodName(int foodId)
{
    for(auto food : m_foodList) {
        if(food.second->id() == foodId) {
            return food.second->name();
        }
    }

    return "";
}

void FoodListForm::onRemoveFilterRequested()
{
    for(auto widget : m_foodInfoWidgets) {
        widget.second->show();
    }
}

void FoodListForm::setupFoodList(std::map<QString, std::shared_ptr<Food> > foodList)
{
    m_foodList = foodList;
    setupFoodListWidgets();
}
