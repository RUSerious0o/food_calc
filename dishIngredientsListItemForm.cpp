#include "dishIngredientsListItemForm.h"
#include "ui_dishIngredientsListItemForm.h"

DishIngredientsListItemForm::DishIngredientsListItemForm(const std::shared_ptr<Food> food, int weight, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishIngredientsListItemForm),
    m_food(food),
    m_weight(weight)
{
    ui->setupUi(this);

    ui->nameLabel->setText(food->name());
    ui->weightLabel->setText(QString("%1").arg(m_weight));
}

DishIngredientsListItemForm::~DishIngredientsListItemForm()
{
    delete ui;
}

void DishIngredientsListItemForm::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        emit itemClicked(m_food, m_weight);
    }
}
