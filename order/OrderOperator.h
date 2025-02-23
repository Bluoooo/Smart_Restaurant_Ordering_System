#ifndef ORDEROPERATOR_H
#define ORDEROPERATOR_H

#include <ctime>
#include <string>
#include <map>
#include "DishesMapOperator.h"
#include <vector>

// 使用时请修改绝对路径basePath
class OrderOperator
{
public:

    // Get the current time, and store it in the variable sitInTime
    int tableNumber;
    int peopleNumber;
    double totalCost;
    std::string sitInTime;

    // Constructor
    OrderOperator(const int tableNumber,
                const int peopleNumber,
                const std::string WaiterNumber,
                DishesMapOperator* dishesMapOperator);
    // destructor
    ~OrderOperator();

    // get the information for the UI
    // eg [ [name1, quantity1, price1, mark1], [name2, quantity2, price2, mark2], ... ]
    // with mark
    // 返回值为orderedDishes的拷贝
    std::vector<std::vector<std::string>> getUIInfo();

    // without mark
    // eg [ [name1, quantity1, price1], [name2, quantity2, price2], ... ]
    // 返回值为orderedDishes的拷贝
    std::vector<std::vector<std::string>> getUIInfoWithoutMark();

    // modify the order
    void addorder(const std::string& name, int quantity,const std::string remark);
    void deleteorder(const std::string& name, int quantity);
    void clearOrder();

    // get information
    double getTotalCost();
    std::string getWaiterNumber();
    std::string getTableNumber();
    int getPeopleNumber();
    std::string getSitInTime();



    // print the order for debug
    void printOrder();

    // I/O operations
    void loadFromFile();
    void saveToFile();
    void clearFile();
    std::vector<OrderOperator> loadAllOrdersFromFile();

private:
    // 使用时请修改绝对路径basePath
    std::string basePath = "D:\\HUAWEI\\Desktop\\test_1130\\table_orders";  // 添加基础路径成员变量
    std::string getOrderFileName() const {
        return basePath + "/order_table_" + std::to_string(tableNumber) + ".txt";
    }
    DishesMapOperator* dishesMapOperator;

    // waiter number
    std::string WaiterNumber;
    // ordered dishes
    std::vector<std::vector<std::string>> orderedDishes;
    // eg [ [name1, quantity1, price1, mark1], [name2, quantity2, price2, mark2], ... ]


};



#endif // ORDEROPERATOR_H
