#include "OrderOperator.h"
#include "DishesMapOperator.h"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>
#include <iostream>

OrderOperator::OrderOperator(const int tableNumber, 
                const int peopleNumber, 
                const std::string WaiterNumber,           
                DishesMapOperator* dishesMapOperator) {
    this->tableNumber = tableNumber;
    this->peopleNumber = peopleNumber;
    this->WaiterNumber = WaiterNumber;
    this->dishesMapOperator = dishesMapOperator;

    this->totalCost = 0.0;

    // 获取当前时间
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    // 格式化时间为字符串，只保留小时、分钟、秒
    std::ostringstream oss;
    oss << std::put_time(localTime, "%H:%M:%S");
    this->sitInTime = oss.str();
};

OrderOperator::~OrderOperator() {
    clearFile();
}

std::vector<std::vector<std::string>> OrderOperator::getUIInfo() {
    loadFromFile();
    // get the information for the UI
    // eg [ [name1, quantity1, price1, mark1], [name2, quantity2, price2, mark2], ... ]
    // with mark
    return orderedDishes;
};

std::vector<std::vector<std::string>> OrderOperator::getUIInfoWithoutMark() {
    // without mark
    // eg [ [name1, quantity1, price1], [name2, quantity2, price2], ... ]
    std::vector<std::vector<std::string>> info;
    for (const auto& dish : orderedDishes) {
        std::vector<std::string> dish_copy;
        dish_copy.push_back(dish[0]);
        dish_copy.push_back(dish[1]);
        dish_copy.push_back(dish[2]);
        info.push_back(dish_copy);
    }
    return info;
    };

void OrderOperator::addorder(const std::string &name, int quantity, const std::string remark){
    // eg [ [name1, quantity1, price1, mark1], [name2, quantity2, price2, mark2], ... ]
    // If the dish is already ordered, increase the quantity
    // 输入验证
    try {
        // 验证菜品是否存在并获取价格
        float price = dishesMapOperator->getDishPriceByName(name);

        // 查找是否已存在该菜品
        for (auto& dish : orderedDishes) {
            if (dish.size() != 4) {
                continue;  // 跳过格式不正确的记录
            }

            if (dish[0] == name) {
                try {
                    int currentQuantity = std::stoi(dish[1]);
                    dish[1] = std::to_string(currentQuantity + quantity);
                    dish[3] = remark;
                    saveToFile();
                    return;
                } catch (const std::exception& e) {
                    throw std::runtime_error("数量转换失败: " + std::string(e.what()));
                }
            }
        }

        // 加新菜品
        orderedDishes.push_back({
            name,
            std::to_string(quantity),
            std::to_string(price),
            remark
        });
        saveToFile();

    } catch (const std::exception& e) {
        throw std::runtime_error("添加菜品失败: " + std::string(e.what()));
    }
}

void OrderOperator::deleteorder(const std::string& name, int quantity) {
    if (name.empty()) {
        throw std::invalid_argument("菜品名称不能为空");
    }
    if (quantity <= 0) {
        throw std::invalid_argument("删除数量必须为正数");
    }

    bool found = false;
    for (auto it = orderedDishes.begin(); it != orderedDishes.end(); ) {
        if (it->size() != 4) {
            ++it;
            continue;  // 跳过格式不正确的记录
        }

        if ((*it)[0] == name) {
            found = true;
            try {
                int currentQuantity = std::stoi((*it)[1]);
                if (currentQuantity <= quantity) {
                    // 如果要删除的数量大于等于现有数量，删除整个记录
                    it = orderedDishes.erase(it);
                } else {
                    // 否则减少数量
                    (*it)[1] = std::to_string(currentQuantity - quantity);
                    ++it;
                }
                saveToFile();
                return;
            } catch (const std::exception& e) {
                throw std::runtime_error("数量转换失败: " + std::string(e.what()));
            }
        } else {
            ++it;
        }
    }

    if (!found) {
        throw std::runtime_error("找不到指定的菜品: " + name);
    }
}

void OrderOperator::clearOrder() {
    orderedDishes.clear();
    totalCost = 0.0;
    clearFile();
}

//-----------methods for get----------------------------------------------
double OrderOperator::getTotalCost() {
    double total = 0.0f;
    for (const auto& dish : orderedDishes) {
        if (dish.size() != 4) {
            continue;  // 跳过格式不正确的记录
        }

        try {
            double price = std::stod(dish[2]);
            int quantity = std::stoi(dish[1]);
            total += price * quantity;
        } catch (const std::exception& e) {
            std::cerr << "计算总价时出错: " << e.what() << std::endl;
            continue;
        }
    }
    totalCost = total;
    saveToFile();
    return total;
}

std::string OrderOperator::getWaiterNumber() {
    loadFromFile();
    return WaiterNumber;
}

std::string OrderOperator::getTableNumber() {
    loadFromFile();
    return std::to_string(tableNumber);
}

int OrderOperator::getPeopleNumber() {
    loadFromFile();
    return peopleNumber;
}

std::string OrderOperator::getSitInTime() {
    loadFromFile();
    return sitInTime;
}

//-------------------I/O operations----------------------------------------------
// Define a structure to hold dish information
struct DishInfo {
    std::string name;
    int quantity;
    float price;
};

void OrderOperator::loadFromFile() {
    std::string currentFile = getOrderFileName();
    std::ifstream inFile(currentFile);
    if (!inFile.is_open()) {
        // 如果文件不存在，创建一个新的文件
        std::ofstream outFile(currentFile);
        outFile.close();
        return;
    }

    try {
        orderedDishes.clear();
        std::string line;

        // 读取订单基本信息
        if (std::getline(inFile, line)) {
            std::istringstream iss(line);
            if (!(iss >> tableNumber >> peopleNumber >> totalCost >> sitInTime >> WaiterNumber)) {
                throw std::runtime_error("订单基本信息格式错误");
            }

            // 验证数据有效性
            if (tableNumber <= 0 || peopleNumber <= 0 || WaiterNumber.empty()) {
                throw std::runtime_error("订单基本信息无效");
            }
        }

        // 读取菜品信息
        float calculatedTotal = 0.0f;  // 用于验证总价
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string dishName;
            std::string quantity;
            std::string price;
            std::string mark;

            if(iss >> dishName >> quantity >> price >> mark){
                orderedDishes.push_back({dishName, quantity, price, mark});
                totalCost += std::stof(price) * std::stoi(quantity);
            }else{
                std::cerr << "警告: 无效的菜品信息，跳过" << std::endl;
                continue;
            }


            // if (iss >> dishName >> quantity) {
            //     if (quantity <= 0) continue;

            //     try {
            //         float price = dishesMapOperator->getDishPriceByName(dishName);
            //         orderedDishes[dishName] = quantity;
            //         calculatedTotal += price * quantity;
            //     } catch (const std::exception& e) {
            //         std::cerr << "警告: 跳过无效菜品 " << dishName << std::endl;
            //     }

        }

        // 验证总价是否匹配
    } catch (const std::exception& e) {
        inFile.close();
        throw std::runtime_error("读取订单失败: " + std::string(e.what()));
    }

    inFile.close();
}


void OrderOperator::saveToFile() {
    std::string currentFile = getOrderFileName();
    std::ofstream outFile(currentFile, std::ios::trunc);
    if (!outFile.is_open()) {
        // 如果文件不存在，创建一个新的文件
        std::ofstream newFile(currentFile);
        newFile.close();
        // 重新打开文件
        outFile.open(currentFile);
    }

    try {
        // 验证数据有效性
        if (tableNumber <= 0 || peopleNumber <= 0 || WaiterNumber.empty()) {
            throw std::runtime_error("订单基本信息无效");
        }

        outFile << tableNumber << " "
               << peopleNumber << " "
               << totalCost << " "
               << sitInTime << " "
               << WaiterNumber << "\n";

        for (const auto& dish : orderedDishes) {
            if (dish.size() != 4) {
                std::cerr << "警告: 无效的菜品信息，跳过" << std::endl;
                continue;
            }
            outFile << dish[0] << " " << dish[1] << " " << dish[2] << " " << dish[3] << "\n";
        }

        // for (const auto& pair : orderedDishes) {
        //     if (pair.second <= 0) continue;  // 跳过无效数量
        //     try {
        //         // 验证菜品是否存在
        //         dishesMapOperator->getDishPriceByName(pair.first);
        //         outFile << pair.first << " " << pair.second << "\n";
        //     } catch (const std::exception& e) {
        //         std::cerr << "警告: 跳过无效菜品 " << pair.first << std::endl;
        //     }
        // }
    } catch (const std::exception& e) {
        outFile.close();
        throw std::runtime_error("保存订单失败: " + std::string(e.what()));
    }

    outFile.close();
}

void OrderOperator::clearFile() {
    try {
        std::string currentFile = getOrderFileName();
        std::ofstream outFile(currentFile, std::ios::trunc);
        if (!outFile.is_open()) {
            throw std::runtime_error("无法打开文件进行清除操作");
        }
        outFile.close();
    } catch (const std::exception& e) {
        std::cerr << "清除文件失败: " << e.what() << std::endl;
    }
}


//-------------------print the order for debug----------------------------------------------
void OrderOperator::printOrder() {
    std::cout<<"TableNumber:"<<tableNumber<<std::endl;
    std::cout<<"PeopleNumber:"<<peopleNumber<<std::endl;
    std::cout<<"SitInTime:"<<sitInTime<<std::endl;
    std::cout<<"WaiterNumber:"<<WaiterNumber<<std::endl;
    std::cout<<"TotalCost:"<<totalCost<<std::endl;

    for (const auto& dish : orderedDishes) {
        std::cout << dish[0] << " " << dish[1] << " " << dish[2] << " " << dish[3] << std::endl;
    }
}

