#ifndef PRODUCTSLISTITEM_H
#define PRODUCTSLISTITEM_H

#include <QWidget>
#include <QMouseEvent>

#include <memory>

#include "food.h"

namespace Ui {
class ProductsListItem;
}

class ProductsListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsListItem(std::shared_ptr<Food>, QWidget *parent = nullptr);

    ~ProductsListItem();

    int presetHeight() const;
    const std::shared_ptr<Food> food() const;

    double protein() const;
    double fats() const;
    double carbohydrates() const;
    double calories() const;

signals:
    void clicked(const std::shared_ptr<Food> food);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::ProductsListItem *ui;
    std::shared_ptr<Food> m_food;
    int m_ingredientId;

    const char *EDIT_ICON_FILENAME = "res/edit_icon.jpg";
    const int PRESET_HEIGHT = 40;           // костыль, до реализации qss
};

#endif // PRODUCTSLISTITEM_H
