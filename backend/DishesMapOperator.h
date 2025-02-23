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
    // ���캯��
    DishesMapOperator();

    // �������� �ᱣ��DishesMap���ļ�
    ~DishesMapOperator();

    // ����DishesMap���ļ���ÿ���޸�DishesMap����Ҫ����
    void saveToFile() const;

    // Here the map is public for better operations like transversing
        // However, it is commended to use the member functions or ADD more member to operate the DishesMap
        std::map<int, std::vector<Dish>> DishesMap;

        // ����ǰ��ʹ�õ�QMap
        // eg:
        // {1: [["dish1", "10.0", "description1", "icon1.png"], ["dish2", "20.0", "description2", "icon2.png"]]
        // 2: [["dish3", "30.0", "description3", "icon3.png"], ["dish4", "40.0", "description4", "icon4.png"]]
        // }

        QMap<int, QVector<QVector<QString>>> getQmap() const;
    // ���Dishʵ��
    void addDish(
            const std::string& name,
            const std::string& label,
            float price,
            const std::string& description,
            const std::string& icon_address);

    // ɾ��Dishʵ��
    void removeDishByName(const std::string& name);

    // �޸�Dishʵ��
    //void updateDish(const std::string& label, const std::string& name, const Dish& newDish);


    // �޸���ص��෽��
    // �޸�Dishʵ����Name
    void updateDishName(const std::string& name, const std::string& newName);
    // �޸�Dishʵ����Label
    void updateDishLabel(const std::string& name, const std::string& newLabel);
    // �޸�Dishʵ����Price
    void updateDishPrice(const std::string& name, float newPrice);
    // �޸�Dishʵ����Description
    void updateDishDescription(const std::string& name, const std::string& newDescription);
    // �޸�Dishʵ����IconAddress
    void updateDishIconAddress(const std::string& name, const std::string& newIconAddress);


    // ͨ��name��ȡDishʵ��
    // If the name is not found, throw an error
    // ͨ��name��ȡDishʵ����ָ��
        Dish* getDishPointerByName(const std::string& name);

        float getDishPriceByName(const std::string& name) const;

    // ��ȡ�ض�Label������Dishʵ��
    std::vector<Dish*> getDishsPointerByLabel(const std::string& name) const;

    // This function is only for testing
       void printAllDishes() const;
       std::list<std::string> getAllDishesAsList() const;
       void printQmap() const;
       // ���һ���µĲ��Է���
       void testAndPrintQmap() const;
       void clearFile();
       // ���ļ���ȡDishesMap


private:
    std::string filename = "D:\\HUAWEI\\Desktop\\test_1130\\dishes_data";
    void loadFromFile();


    // ��ʼ��DishesMap
    void initialize();
};

#endif // FOOD_MAP_H
