#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QDebug>

#include <QWidget>
#include <QString>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QTextStream>
#include <QDate>
#include <QTime>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include <map>
#include <memory>
#include <vector>

#include "food.h"
#include "dish.h"

class DataStorage : public QObject
{
    Q_OBJECT

public:
    static DataStorage& getInstance() {
        static DataStorage instance;
        return instance;
    }

    enum FoodType {
        IngredientType = 1,
        DishType = 2
    };

    struct ConsumedFood {
        QTime time;
        int recordId;
        int foodWeight;
        std::shared_ptr<Food> food;
    };

    bool addFoodName(const QString &foodName, const FoodType foodType);
    bool editFoodName(int dishId, const QString &oldFoodName, const QString& newDishName, const FoodType, double newProteins = 0, double newFats = 0, double newCarbohs = 0);
    int getFoodId(const QString &dishName, FoodType type);    

    std::map<QString, std::shared_ptr<Food>> ingredientsMap();
    bool addIngredient(const QString &ingredientName, double proteins, double fats, double carbohs);
    bool editIngredient(int ingredientId, const QString &oldName, const QString &newName, double proteins, double fats, double carbohs);
    bool removeIngredient(int ingredientId, const QString &ingredientName);

    std::map<QString, std::shared_ptr<Food>> dishesMap(int dishId = -1);
    bool setDishIngredient(int dishId, int ingredientId, int amt);
    std::map<int, std::pair<std::shared_ptr<Food>, int>> dishIngredients(int dishId);
    bool removeDishIngredient(int dishId, int ingredientId);
    bool removeDish(int dishId, const QString &dishName);

    std::map<QString, std::shared_ptr<Food>> fullFoodMap();

    void exportIngredientsDB();

    bool setWeight(const QString &date, double weight, int userId = -1);
    bool addConsumedFood(const QDate &date, int timeMinutes, std::shared_ptr<Food> food, int foodWeight, int userId = -1);
    bool removeConsumedFood(int recordId);

    std::map<int, ConsumedFood> consumedFood(const QDate &date, int userId = -1);

signals:
    void ingredientAdded(std::shared_ptr<Food>);
    void ingredientEdited(const QString &oldIngredientName, std::shared_ptr<Food> newValue);
    void ingredientRemoved(const QString &ingredientName);

    void dishAdded(std::shared_ptr<Food>);
    void dishRemoved(const QString &dishName);
    void dishesEdited(std::map<QString, std::shared_ptr<Food>> changedDishes);

    void foodConsumed(ConsumedFood);
    void consumedFoodRemoved(int recordId);

private:
    DataStorage();
    DataStorage(const DataStorage&) = delete;
    DataStorage& operator=(const DataStorage&) = delete;

    const QString INGREDIENTS_FILEPATH = ":/ingredients/productsDB.txt";
    const QString EXPORT_INGREDIENTS_FILEPATH = "./ingredients.txt";

    const QString DB_NAME = "foodCalcDb";
    const QString USER_NAME = "RUSeriousOo";
    const QString USER_PASSWORD = "d1d2d3d4d5d6";
    const int USER_ID = 1;                            // до тех пор, пока не будет реализована фича отслеживания нескольких пользователей

    const QString FOOD_TABLE_NAME = "food";
    const QStringList FOOD_TABLE_COLUMNS { "id", "name", "type" };

    const QString DISHES_CONSISTENCY_TABLE_NAME = "dish_consist";
    const QStringList DISHES_CONSISTENCY_TABLE_COLUMNS { "dish_id", "ingred_id", "ingred_amt", "key" };

    const QString FOOD_CONSUMPTION_TABLE_NAME = "food_consumption";
    const QStringList FOOD_CONSUMPTION_TABLE_COLUMNS { "date", "time_period", "ingred_id", "dish_id", "user_id", "amt" };

    const QString INGREDIENTS_PFC_TABLE_NAME = "ingredients_PFC";
    const QStringList INGREDIENTS_PFC_TABLE_COLUMNS { "ingred_id", "proteins", "fats", "carbohs" };

    const QString USER_DYMAMICS_TABLE_NAME = "weight_dynamics";
    const QStringList USER_DYMAMICS_TABLE_COLUMNS { "user_id", "date", "weight", "key" };

    const QString CONSUMPTION_DIARY_TABLE_NAME = "consumption_diary";
    const QStringList CONSUMPTION_DIARY_TABLE_COLUMNS { "record_id", "user_id", "date", "time", "food_id", "food_weight" };

    const QString DATE_FORMAT = "dd.MM.yyyy";

    QFile ingredientsFile;
    QSqlDatabase db;

    bool setupDb();
    std::map<int, std::shared_ptr<Food>> ingredientsById();
    void importIngredientsDB();
    bool checkQueryError(const QSqlQuery&);
};

#endif // DATASTORAGE_H
