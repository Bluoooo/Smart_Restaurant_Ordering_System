// FILE: food_map.h
#ifndef FOOD_MAP_H
#define FOOD_MAP_H

#include "Dish.h"
#include <map>
#include <vector>
#include <string>
#include <Qmap>
#include <Qvector>
#include <Qstring>
class DishesMapOperator {
public:
    // 构造函数
    DishesMapOperator();

    // 析构函数 会保存DishesMap到文件
    ~DishesMapOperator();

    // 保存DishesMap到文件，每次修改DishesMap后都需要调用
    void saveToFile() const;

    // Here the map is public for better operations like transversing
        // However, it is commended to use the member functions or ADD more member to operate the DishesMap
        std::map<int, std::vector<Dish>> DishesMap;

        // 返回前端使用的QMap
        // eg:
        // {1: [["dish1", "10.0", "description1", "icon1.png"], ["dish2", "20.0", "description2", "icon2.png"]]
        // 2: [["dish3", "30.0", "description3", "icon3.png"], ["dish4", "40.0", "description4", "icon4.png"]]
        // }

        QMap<int, QVector<QVector<QString>>> getQmap() const;
    // 添加Dish实例
    void addDish(
            const std::string& name,
            const std::string& label,
            float price,
            const std::string& description,
            const std::string& icon_address);

    // 删除Dish实例
    void removeDishByName(const std::string& name);

    // 修改Dish实例
    //void updateDish(const std::string& label, const std::string& name, const Dish& newDish);


    // 修改相关的类方法
    // 修改Dish实例的Name
    void updateDishName(const std::string& name, const std::string& newName);
    // 修改Dish实例的Label
    void updateDishLabel(const std::string& name, const std::string& newLabel);
    // 修改Dish实例的Price
    void updateDishPrice(const std::string& name, float newPrice);
    // 修改Dish实例的Description
    void updateDishDescription(const std::string& name, const std::string& newDescription);
    // 修改Dish实例的IconAddress
    void updateDishIconAddress(const std::string& name, const std::string& newIconAddress);


    // 通过name获取Dish实例
    // If the name is not found, throw an error
    // 通过name获取Dish实例的指针
        Dish* getDishPointerByName(const std::string& name);

        float getDishPriceByName(const std::string& name) const;

    // 获取特定Label的所有Dish实例
    std::vector<Dish*> getDishsPointerByLabel(const std::string& name) const;

    // This function is only for testing
       void printAllDishes() const;
       std::list<std::string> getAllDishesAsList() const;
       void printQmap() const;
       // 添加一个新的测试方法
       void testAndPrintQmap() const;
       void clearFile();
       // 从文件读取DishesMap


private:
    std::string filename = "D:\\HUAWEI\\Desktop\\test_1130\\dishes_data";
    void loadFromFile();


    // 初始化DishesMap
    void initialize();
};

#endif // FOOD_MAP_H
