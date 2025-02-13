#ifndef FOODLISTFORM_H
#define FOODLISTFORM_H

#include <QDebug>

#include <QByteArray>
#include <QFile>
#include <QVBoxLayout>
#include <QList>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>

#include <map>
#include <algorithm>
#include <cmath>
#include <memory>

#include "FoodList/productslistitem.h"
#include "food.h"
#include "datastorage.h"

namespace Ui {
class FoodListForm;
}

class FoodListForm : public QWidget
{
    Q_OBJECT

public:
    explicit FoodListForm (QWidget *parent = nullptr);
    ~FoodListForm();    

public slots:
    void onIngredientFilterAdded(const QString&);

    void onSortByPFCClicked();
    void onSortByNameClicked();
    void onRemoveFilterRequested();

signals:
    void itemClicked(const std::shared_ptr<Food>);

protected:
    virtual void setupUniqueSlots() = 0;

    void setupFoodList(std::map<QString, std::shared_ptr<Food>>);
    void addFood(std::shared_ptr<Food>, int index = -1);
    void addFoodWidget(std::shared_ptr<Food>, int index = -1);
    void removeFood(const QString &foodName);
    const QString foodName(int foodId);

private:
    Ui::FoodListForm *ui;
    std::map<QString, std::shared_ptr<Food>> m_foodList;
    std::map<QString, ProductsListItem*> m_foodInfoWidgets;

    void setupFoodListWidgets();
    void setupSlots();
};

#endif // FOODLISTFORM_H
