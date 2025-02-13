#include "datastorage.h"

DataStorage::DataStorage()
    : ingredientsFile(INGREDIENTS_FILEPATH)
    , db(QSqlDatabase::addDatabase("QSQLITE"))
{
    if(!setupDb()) {
        qDebug() << "Database initialization failed!";
    }
}

std::map<QString, std::shared_ptr<Food>> DataStorage::ingredientsMap()
{
    std::map<QString, std::shared_ptr<Food>> result;
    auto query = db.exec(QString("SELECT * FROM %1 JOIN %2 ON %1.%3 = %2.%4")
                         .arg(FOOD_TABLE_NAME)
                         .arg(INGREDIENTS_PFC_TABLE_NAME)
                         .arg(FOOD_TABLE_COLUMNS[0])
                         .arg(INGREDIENTS_PFC_TABLE_COLUMNS[0]));
    if(query.lastError().databaseText() != "") {
        qDebug() << query.lastError().databaseText();
        return result;
    }

    while(query.next()) {
        std::shared_ptr<Food> temp (new Food(query.value(INGREDIENTS_PFC_TABLE_COLUMNS[0]).toInt(),
                              query.value(FOOD_TABLE_COLUMNS[1]).toString(),
                              query.value(INGREDIENTS_PFC_TABLE_COLUMNS[1]).toDouble(),
                              query.value(INGREDIENTS_PFC_TABLE_COLUMNS[2]).toDouble(),
                              query.value(INGREDIENTS_PFC_TABLE_COLUMNS[3]).toDouble()));
        result[query.value(FOOD_TABLE_COLUMNS[1]).toString()] = temp;
    }

    return result;
}

std::map<QString, std::shared_ptr<Food>> DataStorage::dishesMap(int dishId)
{
    std::map<QString, std::shared_ptr<Food>> result;
    auto queryAppend = QString(" AND %4 IN (%5)").arg(FOOD_TABLE_COLUMNS[0]).arg(dishId);
    auto dishesQuery = db.exec(QString("SELECT * FROM %1 WHERE %2 = \'%3\'%4")
                               .arg(FOOD_TABLE_NAME)
                               .arg(FOOD_TABLE_COLUMNS[2])
                               .arg(DishType)
                               .arg(dishId == -1 ? "" :  queryAppend));

    std::map<int, std::shared_ptr<Food>> ingredients;
    while(dishesQuery.next()) {
        if(ingredients.empty()) {
            ingredients = ingredientsById();
        }

        int dishId = dishesQuery.value(FOOD_TABLE_COLUMNS[0]).toInt();
        std::shared_ptr<Dish> temp (new Dish(dishId, dishesQuery.value(FOOD_TABLE_COLUMNS[1]).toString()));
        auto ingredientsQuery = db.exec(QString("SELECT * FROM %1 WHERE %2 = \'%3\'")
                                   .arg(DISHES_CONSISTENCY_TABLE_NAME)
                                   .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[0])
                                   .arg(dishId));
        while(ingredientsQuery.next()) {
            int ingredientId = ingredientsQuery.value(DISHES_CONSISTENCY_TABLE_COLUMNS[1]).toInt();
            temp->addOrEditIngredient(ingredients[ingredientId],
                                      ingredientsQuery.value(DISHES_CONSISTENCY_TABLE_COLUMNS[2]).toInt());
        }

        result[temp->name()] = temp;
    }

    return result;
}

bool DataStorage::addIngredient(const QString &ingredientName, double proteins, double fats, double carbohs)
{
    addFoodName(ingredientName, IngredientType);
    auto result = db.exec(QString("INSERT INTO %1 (%2, %3, %4, %5) VALUES (\'%6\', \'%7\', \'%8\', \'%9\')")
                          .arg(INGREDIENTS_PFC_TABLE_NAME)
                          .arg(INGREDIENTS_PFC_TABLE_COLUMNS[0])
                          .arg(INGREDIENTS_PFC_TABLE_COLUMNS[1])
                          .arg(INGREDIENTS_PFC_TABLE_COLUMNS[2])
                          .arg(INGREDIENTS_PFC_TABLE_COLUMNS[3])
                          .arg(getFoodId(ingredientName, IngredientType))
                          .arg(proteins)
                          .arg(fats)
                          .arg(carbohs));

    emit ingredientAdded(std::shared_ptr<Food>(new Food(getFoodId(ingredientName, IngredientType), ingredientName, proteins, fats, carbohs)));
    return checkQueryError(result);
}

bool DataStorage::editIngredient(int ingredientId, const QString &oldName, const QString &newName, double proteins, double fats, double carbohs)
{    
    // т.к. имя продукта имеет ограничение "уникальное", необходимо сначала обновить значения БЖУ (сигналим старым именем), и тольео потом - пытаться обновить имя
    auto result = db.exec(QString("UPDATE %1 SET %2 = \'%3\', %4 = \'%5\', %6 = \'%7\' WHERE %8 = \'%9\'")
                          .arg(INGREDIENTS_PFC_TABLE_NAME)
                          .arg(INGREDIENTS_PFC_TABLE_COLUMNS[1])
                          .arg(proteins)
                          .arg(INGREDIENTS_PFC_TABLE_COLUMNS[2])
                          .arg(fats)
                          .arg(INGREDIENTS_PFC_TABLE_COLUMNS[3])
                          .arg(carbohs)
                          .arg(INGREDIENTS_PFC_TABLE_COLUMNS[0])
                          .arg(ingredientId));
    checkQueryError(result);

    emit ingredientEdited(oldName, std::shared_ptr<Food>(new Food(ingredientId, oldName, proteins, fats, carbohs)));
    editFoodName(ingredientId, oldName, newName, FoodType::IngredientType, proteins, fats, carbohs);

    // после того, как обновили ингредиент, находим блюда, на которые данное изменение повлияло, и сигналим их
    result = db.exec(QString("SELECT * FROM %1 WHERE %2 = \'%3\' AND %4 IN (SELECT %5 FROM %6 WHERE %7 = \'%8\')")
                     .arg(FOOD_TABLE_NAME)
                     .arg(FOOD_TABLE_COLUMNS[2])
                     .arg(DishType)
                     .arg(FOOD_TABLE_COLUMNS[0])
                     .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[0])
                     .arg(DISHES_CONSISTENCY_TABLE_NAME)
                     .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[1])
                     .arg(ingredientId));
    checkQueryError(result);

    while(result.next()) {
        emit dishesEdited(dishesMap(result.value(FOOD_TABLE_COLUMNS[0]).toInt()));
    }
    return checkQueryError(result);
}

bool DataStorage::removeDishIngredient(int dishId, int ingredientId)
{
    auto result = db.exec(QString("DELETE FROM %1 WHERE %2 = \'%3_%4\'")
                          .arg(DISHES_CONSISTENCY_TABLE_NAME)
                          .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[3])
                          .arg(dishId)
                          .arg(ingredientId));

    emit dishesEdited(dishesMap(dishId));
    return checkQueryError(result);
}

bool DataStorage::addFoodName(const QString &foodName, const FoodType foodType)
{
    auto result = db.exec(QString("INSERT INTO %1 (%2, %3) VALUES (\"%4\", \'%5\')")
                          .arg(FOOD_TABLE_NAME)
                          .arg(FOOD_TABLE_COLUMNS[1])
                          .arg(FOOD_TABLE_COLUMNS[2])
                          .arg(foodName)
                          .arg(foodType));

    if(foodType == FoodType::DishType) {
        emit dishAdded(std::shared_ptr<Food>(new Dish(getFoodId(foodName, FoodType::DishType), foodName)));
    }
    return checkQueryError(result);
}

bool DataStorage::editFoodName(int foodId, const QString &oldFoodName, const QString &newFoodName, const FoodType foodType, double newProteins, double newFats, double newCarbohs)
{
    auto result = db.exec(QString("UPDATE %1 SET %2 = \"%3\" WHERE %4 = \"%5\"")
                          .arg(FOOD_TABLE_NAME)
                          .arg(FOOD_TABLE_COLUMNS[1])
                          .arg(newFoodName)
                          .arg(FOOD_TABLE_COLUMNS[0])
                          .arg(foodId));

    if(foodType == DishType) {
        if(result.lastError().databaseText() == "") {
            emit dishesEdited(dishesMap(foodId));
        }
    } else if (foodType == IngredientType) {
        if(result.lastError().databaseText() == "") {
            emit ingredientEdited(oldFoodName, std::shared_ptr<Food>(new Food(foodId, newFoodName, newProteins, newFats, newCarbohs)));
        } else {
            emit ingredientEdited(oldFoodName, std::shared_ptr<Food>(new Food(foodId, oldFoodName, newProteins, newFats, newCarbohs)));
        }
    }

    return checkQueryError(result);
}

int DataStorage::getFoodId(const QString &dishName, FoodType type)
{
    auto result = db.exec(QString("SELECT %1 FROM %2 WHERE %3 = \'%4\' AND %5 = \'%6\'")
                          .arg(FOOD_TABLE_COLUMNS[0])
                          .arg(FOOD_TABLE_NAME)
                          .arg(FOOD_TABLE_COLUMNS[1])
                          .arg(dishName)
                          .arg(FOOD_TABLE_COLUMNS[2])
                          .arg(type));
    if(result.lastError().databaseText() == "")  {
        result.next();
        return result.value(FOOD_TABLE_COLUMNS[0]).toInt();
    } else {
        return -1;
    }
}

bool DataStorage::removeIngredient(int ingredientId, const QString &ingredientName)
{
    auto involvedDishesQuery = db.exec(QString("SELECT * FROM %1 WHERE %2 = \'%3\' AND %4 IN (SELECT %5 FROM %6 WHERE %7 = \'%8\')")
                     .arg(FOOD_TABLE_NAME)
                     .arg(FOOD_TABLE_COLUMNS[2])
                     .arg(DishType)
                     .arg(FOOD_TABLE_COLUMNS[0])
                     .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[0])
                     .arg(DISHES_CONSISTENCY_TABLE_NAME)
                     .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[1])
                     .arg(ingredientId));
    checkQueryError(involvedDishesQuery);

    auto result = db.exec(QString("DELETE FROM %1 WHERE %2 = \'%3\'")
                          .arg(FOOD_TABLE_NAME)
                          .arg(FOOD_TABLE_COLUMNS[0])
                          .arg(ingredientId));
    checkQueryError(result);

    result = db.exec(QString("DELETE FROM %1 WHERE %2 = \'%3\'")
                     .arg(DISHES_CONSISTENCY_TABLE_NAME)
                     .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[1])
                     .arg(ingredientId));
    checkQueryError(result);

    result = db.exec(QString("DELETE FROM %1 WHERE %2 = \'%3\'")
                     .arg(INGREDIENTS_PFC_TABLE_NAME)
                     .arg(INGREDIENTS_PFC_TABLE_COLUMNS[0])
                     .arg(ingredientId));

    emit ingredientRemoved(ingredientName);
    while(involvedDishesQuery.next()) {
        emit dishesEdited(dishesMap(involvedDishesQuery.value(FOOD_TABLE_COLUMNS[0]).toInt()));
    }
    return checkQueryError(result);
}

bool DataStorage::setDishIngredient(int dishId, int ingredientId, int amt)
{
    auto result = db.exec(QString("INSERT OR REPLACE INTO %1 (%2, %3, %4, %5) VALUES (%6, %7, %8, \"%9\")")
                          .arg(DISHES_CONSISTENCY_TABLE_NAME)
                          .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[0])
                          .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[1])
                          .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[2])
                          .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[3])
                          .arg(dishId)
                          .arg(ingredientId)
                          .arg(amt)
                          .arg(QString("%1_%2").arg(dishId).arg(ingredientId)));

    emit dishesEdited(dishesMap(dishId));
    return checkQueryError(result);
}

std::map<int, std::pair<std::shared_ptr<Food>, int>> DataStorage::dishIngredients(int dishId)
{
    auto query = db.exec(QString("SELECT * FROM %1 WHERE %2 = \"%3\"")
                         .arg(DISHES_CONSISTENCY_TABLE_NAME)
                         .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[0])
                         .arg(dishId));

    std::map<int, std::pair<std::shared_ptr<Food>, int>> result;
    auto ingredients = ingredientsById();
    while(query.next()) {
        int ingredientId = query.value(DISHES_CONSISTENCY_TABLE_COLUMNS[1]).toInt();
        result[ingredientId] = { ingredients[ingredientId], query.value(DISHES_CONSISTENCY_TABLE_COLUMNS[2]).toInt() };
    }

    return result;
}

bool DataStorage::removeDish(int dishId, const QString &dishName)
{
    auto result = db.exec(QString("DELETE FROM %1 WHERE %2 = \'%3\'")
                          .arg(DISHES_CONSISTENCY_TABLE_NAME)
                          .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[0])
                          .arg(dishId));
    checkQueryError(result);

    result = db.exec(QString("DELETE FROM %1 WHERE %2 = \'%3\'")
                     .arg(FOOD_TABLE_NAME)
                     .arg(FOOD_TABLE_COLUMNS[0])
                     .arg(dishId));

    emit dishRemoved(dishName);
    return checkQueryError(result);
}

std::map<QString, std::shared_ptr<Food>> DataStorage::fullFoodMap()
{
    auto result = ingredientsMap();
    result.merge(dishesMap());
    return result;
}

void DataStorage::exportIngredientsDB()
{
    QFile exportFile(EXPORT_INGREDIENTS_FILEPATH);
    if(!exportFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Couldn't open export ingredients file!";
        return;
    }

    QTextStream writeStream(&exportFile);
    writeStream.setCodec("UTF-8");
    auto ingredients = ingredientsMap();
    for(auto ingredient : ingredients) {
        writeStream << ingredient.second->codedDescription() << "\n";
    }

    exportFile.close();
}

bool DataStorage::setWeight(const QString &date, double weight, int userId)
{
    auto result = db.exec(QString("INSERT OR REPLACE INTO %1 (%2, %3, %4, %5) VALUES (%6, \'%7\', %8, \"%6_%7\")")
                          .arg(USER_DYMAMICS_TABLE_NAME)
                          .arg(USER_DYMAMICS_TABLE_COLUMNS[0])
                          .arg(USER_DYMAMICS_TABLE_COLUMNS[1])
                          .arg(USER_DYMAMICS_TABLE_COLUMNS[2])
                          .arg(USER_DYMAMICS_TABLE_COLUMNS[3])
                          .arg(userId == -1 ? USER_ID : userId)
                          .arg(date)
                          .arg(weight));

    return checkQueryError(result);
}

bool DataStorage::addConsumedFood(const QDate &date, int timeMinutes, std::shared_ptr<Food> food, int foodWeight, int userId)
{
    auto result = db.exec(QString("INSERT INTO %1 (%2, %3, %4, %5, %6) VALUES (%7, \'%8\', %9, %10, %11)")
                          .arg(CONSUMPTION_DIARY_TABLE_NAME)
                          .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[1])
                          .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[2])
                          .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[3])
                          .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[4])
                          .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[5])
                          .arg(userId == -1 ? USER_ID : userId)
                          .arg(date.toString(DATE_FORMAT))
                          .arg(timeMinutes)
                          .arg(food->id())
                          .arg(foodWeight));
    checkQueryError(result);

    result = db.exec(QString("SELECT * FROM %1 ORDER BY %2 DESC LIMIT 1")
                     .arg(CONSUMPTION_DIARY_TABLE_NAME)
                     .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[0]));
    if(checkQueryError(result)) {
        result.next();
        emit foodConsumed({QTime(0,0,0).addSecs(timeMinutes * 60), result.value(CONSUMPTION_DIARY_TABLE_COLUMNS[0]).toInt(), foodWeight, food});
        return true;
    } else {
        return false;
    }
}

bool DataStorage::removeConsumedFood(int recordId)
{
    auto result = db.exec(QString("DELETE FROM %1 WHERE %2 = \'%3\'")
                          .arg(CONSUMPTION_DIARY_TABLE_NAME)
                          .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[0])
                          .arg(recordId));
    emit consumedFoodRemoved(recordId);
    return checkQueryError(result);
}

std::map<int, DataStorage::ConsumedFood> DataStorage::consumedFood(const QDate &date, int userId)
{
    std::map<int, ConsumedFood> result;
    userId = userId == -1 ? USER_ID : userId;

    auto query = db.exec(QString("SELECT * FROM %1 JOIN %2 ON %1.%3 = %2.%4 WHERE %5 = \'%6\' AND %7 = \'%8\'")
                         .arg(CONSUMPTION_DIARY_TABLE_NAME)
                         .arg(FOOD_TABLE_NAME)
                         .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[4])
                         .arg(FOOD_TABLE_COLUMNS[0])
                         .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[1])
                         .arg(userId)
                         .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[2])
                         .arg(date.toString(DATE_FORMAT)));
    checkQueryError(query);

    std::map<QString, std::shared_ptr<Food>> foodMap;
    while(query.next()) {
        if(foodMap.size() == 0) {
            foodMap = fullFoodMap();
        }

        ConsumedFood cFood;
        cFood.time = QTime(0,0,0).addSecs(query.value(CONSUMPTION_DIARY_TABLE_COLUMNS[3]).toInt() * 60);
        cFood.foodWeight = query.value(CONSUMPTION_DIARY_TABLE_COLUMNS[5]).toInt();
        cFood.recordId = query.value(CONSUMPTION_DIARY_TABLE_COLUMNS[0]).toInt();
        cFood.food = foodMap[query.value(FOOD_TABLE_COLUMNS[1]).toString()];

        result[cFood.recordId] = cFood;
    }

    return result;
}

bool DataStorage::setupDb()
{
    db.setDatabaseName(DB_NAME);
    db.setUserName(USER_NAME);
    db.setPassword(USER_PASSWORD);
    db.open(USER_NAME, USER_PASSWORD);

    auto tables = db.tables();
    if(!tables.contains(FOOD_TABLE_NAME)) {
        auto result = db.exec(QString("CREATE TABLE %1(%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 TEXT UNIQUE NOT NULL, %4 INTEGER NOT NULL)")
                              .arg(FOOD_TABLE_NAME)
                              .arg(FOOD_TABLE_COLUMNS[0])
                              .arg(FOOD_TABLE_COLUMNS[1])
                              .arg(FOOD_TABLE_COLUMNS[2]));
        qDebug() << result.lastError().databaseText();
    }

    if(!tables.contains(DISHES_CONSISTENCY_TABLE_NAME)) {
        auto result = db.exec(QString("CREATE TABLE %1(%2 INTEGER NOT NULL, %3 INTEGER NOT NULL, %4 INTEGER NOT NULL, %5 TEXT UNIQUE NOT NULL)")
                              .arg(DISHES_CONSISTENCY_TABLE_NAME)
                              .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[0])
                              .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[1])
                              .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[2])
                              .arg(DISHES_CONSISTENCY_TABLE_COLUMNS[3]));
        qDebug() << result.lastError().databaseText();
    }

    if(!tables.contains(INGREDIENTS_PFC_TABLE_NAME)) {
        auto result = db.exec(QString("CREATE TABLE %1(%2 INTEGER PRIMARY KEY NOT NULL, %3 REAL NOT NULL, %4 REAL NOT NULL, %5 REAL NOT NULL)")
                              .arg(INGREDIENTS_PFC_TABLE_NAME)
                              .arg(INGREDIENTS_PFC_TABLE_COLUMNS[0])
                              .arg(INGREDIENTS_PFC_TABLE_COLUMNS[1])
                              .arg(INGREDIENTS_PFC_TABLE_COLUMNS[2])
                              .arg(INGREDIENTS_PFC_TABLE_COLUMNS[3]));
        qDebug() << result.lastError().databaseText();
        importIngredientsDB();
    }

    if(!tables.contains(USER_DYMAMICS_TABLE_NAME)) {
        auto result = db.exec(QString("CREATE TABLE %1(%2 INTEGER UNIQUE NOT NULL, %3 TEXT NOT NULL, %4 REAL NOT NULL, %5 TEXT UNIQUE NOT NULL)")
                              .arg(USER_DYMAMICS_TABLE_NAME)
                              .arg(USER_DYMAMICS_TABLE_COLUMNS[0])
                              .arg(USER_DYMAMICS_TABLE_COLUMNS[1])
                              .arg(USER_DYMAMICS_TABLE_COLUMNS[2])
                              .arg(USER_DYMAMICS_TABLE_COLUMNS[3]));
        qDebug() << result.lastError().databaseText();
    }

    if(!tables.contains(CONSUMPTION_DIARY_TABLE_NAME)) {
        auto result = db.exec(QString("CREATE TABLE %1(%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 INTEGER NOT NULL, %4 TEXT NOT NULL, \
                                       %5 INTEGER NOT NULL, %6 INTEGER NOT NULL, %7 INTEGER NOT NULL)")
                              .arg(CONSUMPTION_DIARY_TABLE_NAME)
                              .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[0])
                              .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[1])
                              .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[2])
                              .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[3])
                              .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[4])
                              .arg(CONSUMPTION_DIARY_TABLE_COLUMNS[5]));
        qDebug() << result.lastError().databaseText();
    }

    return true;
}

std::map<int, std::shared_ptr<Food>> DataStorage::ingredientsById()
{
    std::map<int, std::shared_ptr<Food>> result;
    auto query = db.exec(QString("SELECT * FROM %1 JOIN %2 ON %1.%3 = %2.%4")
                         .arg(FOOD_TABLE_NAME)
                         .arg(INGREDIENTS_PFC_TABLE_NAME)
                         .arg(FOOD_TABLE_COLUMNS[0])
                         .arg(INGREDIENTS_PFC_TABLE_COLUMNS[0]));
    if(query.lastError().databaseText() != "") {
        qDebug() << query.lastError().databaseText();
        return result;
    }

    while(query.next()) {
        std::shared_ptr<Food> temp (new Food(query.value(INGREDIENTS_PFC_TABLE_COLUMNS[0]).toInt(),
                              query.value(FOOD_TABLE_COLUMNS[1]).toString(),
                              query.value(INGREDIENTS_PFC_TABLE_COLUMNS[1]).toDouble(),
                              query.value(INGREDIENTS_PFC_TABLE_COLUMNS[2]).toDouble(),
                              query.value(INGREDIENTS_PFC_TABLE_COLUMNS[3]).toDouble()));
        result[query.value(INGREDIENTS_PFC_TABLE_COLUMNS[0]).toInt()] = temp;
    }

    return result;
}

void DataStorage::importIngredientsDB()
{
    if(!ingredientsFile.open(QFile::ReadOnly)) {
        qDebug() << "Ingredients file open error!";
        return;
    }

    while(!ingredientsFile.atEnd()) {
        Food *temp = new Food(ingredientsFile.readLine());
        addIngredient(temp->name(), temp->proteins(), temp->fats(), temp->carbohs());
        delete temp;
    }

    ingredientsFile.close();
}

bool DataStorage::checkQueryError(const QSqlQuery &query)
{
    if(query.lastError().databaseText() == "") {
        return true;
    } else {
        qDebug() << query.lastError().databaseText();
        return false;
    }
}
