#include "productslistitem.h"
#include "ui_productslistitem.h"

#include <QAction>

ProductsListItem::ProductsListItem(std::shared_ptr<Food> food, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductsListItem),
    m_food(food)
{
    ui->setupUi(this);

    ui->name->setText(m_food->name());
    ui->protein->setText(QString("%1").arg(m_food->proteins()));
    ui->fats->setText(QString("%1").arg(m_food->fats()));
    ui->carbohs->setText(QString("%1").arg(m_food->carbohs()));
    ui->calories->setText(QString("%1").arg(m_food->calories()));
    this->setFixedHeight(PRESET_HEIGHT);
}

ProductsListItem::~ProductsListItem()
{
    delete ui;
}

int ProductsListItem::presetHeight() const
{
    return PRESET_HEIGHT;
}

const std::shared_ptr<Food> ProductsListItem::food() const
{
    return m_food;
}

void ProductsListItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        emit clicked(m_food);
    }
}
