// FILE: Dish_map.cpp
#include "DishesMapOperator.h"
#include "Dish.h"
#include "Dish.cpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <QDebug>

DishesMapOperator::DishesMapOperator() {
    initialize();
}

DishesMapOperator::~DishesMapOperator() {
    saveToFile();
}

QMap<int, QVector<QVector<QString>>> DishesMapOperator::getQmap() const {
    QMap<int, QVector<QVector<QString>>> DishesQMap;

    for (const auto& pair : DishesMap) {
        QVector<QVector<QString>> dishes;
        for (const auto& dish : pair.second) {
            QVector<QString> dishInfo;
            dishInfo.push_back(QString::fromStdString(dish.getName()));
            dishInfo.push_back(QString::number(dish.getPrice()));
            dishInfo.push_back(QString::fromStdString(dish.getDescription()));
            dishInfo.push_back(QString::fromStdString(dish.getIconAddress()));
            dishes.push_back(dishInfo);
        }
        DishesQMap[pair.first] = dishes;
    }
    return DishesQMap;


};

void DishesMapOperator::addDish(
    const std::string& name,
    const std::string& label,
    float price,
    const std::string& description,
    const std::string& icon_address) {


    // 检查是否存在同名菜品
    for (const auto& pair : DishesMap) {
        for (const auto& dish : pair.second) {
            if (dish.getName() == name) {
                throw std::runtime_error("已存在同名菜品: " + name);
            }
        }
    }
    std::array<QString, 4> sub_menu = {"Main Dish", "Side Dish", "Dessert", "Drink"};
    // 添加新菜品
    QString qlabel = QString::fromStdString(label);
    auto it = std::find(sub_menu.begin(), sub_menu.end(), qlabel);
    int index;
    if (it != sub_menu.end()) {
            // 计算索引
            index = std::distance(sub_menu.begin(), it);}
    Dish dish(name, label, price, description, icon_address);
    DishesMap[index].push_back(dish);
    saveToFile();
}

void DishesMapOperator::removeDishByName(const std::string& name) {
    bool found = false;
        for (auto& Dishs : DishesMap) {
            auto initialSize = Dishs.second.size();
            Dishs.second.erase(std::remove_if(Dishs.second.begin(), Dishs.second.end(),
                [&](const Dish& Dish) {
                    return Dish.getName() == name;
                }), Dishs.second.end());

            if (Dishs.second.size() < initialSize) {
                found = true;
            }
        }

        if (found) {
            saveToFile();
        } else {
            throw std::runtime_error("Dish with name " + name + " not found");
        }
    }


//void DishesMapOperator::updateDish(const std::string& label, const std::string& name, const Dish& newDish) {
//    auto& Dishs = DishesMap[label];
//    for (auto& Dish : Dishs) {
//        if (Dish.getName() == name) {
//            Dish = newDish;
//            break;
//        }
//    }
//}

//-------------------------------methods for update----------------------------------------

void DishesMapOperator::updateDishName(const std::string& name, const std::string& newName) {
    for (auto& Dishs : DishesMap) {
        for (auto& Dish : Dishs.second) {
            if (Dish.getName() == name) {
                Dish.setName(newName);
                saveToFile();
                return;
            }
        }
    }
    throw std::runtime_error("Dish with name " + name + " not found");
}

void DishesMapOperator::updateDishLabel(const std::string& name, const std::string& newLabel) {
    for (auto& Dishs : DishesMap) {
        for (auto& Dish : Dishs.second) {
            if (Dish.getName() == name) {
                Dish.setLabel(newLabel);
                saveToFile();
                return;
            }
        }
    }
    throw std::runtime_error("Dish with name " + name + " not found");
}

void DishesMapOperator::updateDishPrice(const std::string& name, float newPrice) {
    for (auto& Dishs : DishesMap) {
        for (auto& Dish : Dishs.second) {
            if (Dish.getName() == name) {
                Dish.setPrice(newPrice);
                saveToFile();
                return;
            }
        }
    }
    throw std::runtime_error("Dish with name " + name + " not found");
}

void DishesMapOperator::updateDishDescription(const std::string& name, const std::string& newDescription) {
    for (auto& Dishs : DishesMap) {
        for (auto& Dish : Dishs.second) {
            if (Dish.getName() == name) {
                Dish.setDescription(newDescription);
                saveToFile();
                return;
            }
        }
    }
    throw std::runtime_error("Dish with name " + name + " not found");
}

void DishesMapOperator::updateDishIconAddress(const std::string& name, const std::string& newIconAddress) {
    for (auto& Dishs : DishesMap) {
        for (auto& Dish : Dishs.second) {
            if (Dish.getName() == name) {
                Dish.setIconAddress(newIconAddress);
                saveToFile();
                return;
            }
        }
    }
    throw std::runtime_error("Dish with name " + name + " not found");
}

// ----------------------------------------

Dish* DishesMapOperator::getDishPointerByName(const std::string& name) {
    for (auto& Dishs : DishesMap) {
        for (auto& Dish : Dishs.second) {
            if (Dish.getName() == name) {
                return &Dish;
            }
        }
    }
    throw std::runtime_error("Dish with name " + name + " not found");
}

float DishesMapOperator::getDishPriceByName(const std::string& name) const {
    for (auto& Dishs : DishesMap) {
        for (auto& Dish : Dishs.second) {
            if (Dish.getName() == name) {
                return Dish.getPrice();
            }
        }
    }
    throw std::runtime_error("Dish with name " + name + " not found");
}

std::vector<Dish*> DishesMapOperator::getDishsPointerByLabel(const std::string& label) const {
    std::vector<Dish*> dishes;
    std::array<QString, 4> sub_menu = {"Main Dish", "Side Dish", "Dessert", "Drink"};

    // 将 std::string 转换为 QString
    QString qlabel = QString::fromStdString(label);

    // 使用 QString 进行查找
    auto itt = std::find(sub_menu.begin(), sub_menu.end(), qlabel);
    if (itt != sub_menu.end()) {
        // 计算 sub_menu 中的索引
        int index = std::distance(sub_menu.begin(), itt);

        // 查找 DishesMap 中与索引相关联的菜品
        auto it = DishesMap.find(index);
        if (it != DishesMap.end()) {
            // 添加所有与索引相关的 Dish
            for (const auto& dish : it->second) {
                dishes.push_back(const_cast<Dish*>(&dish)); // 注意 const_cast 的安全性
            }
        }
    }
    return dishes;
}



void DishesMapOperator::initialize() {
    // 检查文件是否存在
    std::ifstream checkFile(filename);
    if (!checkFile.good()) {
        // 如果文件不存在，创建一个空文件
        std::ofstream createFile(filename);
        createFile.close();
    } else {
        checkFile.close();
    }

    // 加载现有数据
    loadFromFile();
}


void DishesMapOperator::saveToFile() const {
    // 使用 ios::trunc 模式以覆写方式打开文件
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    try {
        for (const auto& pair : DishesMap) {
            for (const auto& dish : pair.second) {
                outFile << pair.first << " "
                       << dish.getName() << " "
                       << dish.getPrice() << " "
                       << dish.getDescription() << " "
                       << dish.getIconAddress() << "\n";

                if (outFile.fail()) {
                    throw std::runtime_error("Failed to write to file");
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error while saving: " << e.what() << std::endl;
    }

    outFile.close();
}

// 从文件读取DishesMap
void DishesMapOperator::loadFromFile() {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string label;
        std::string name;
        float price;
        std::string description;
        std::string icon_address;
        while (inFile >> label >> name >> price >> description >> icon_address) {
            Dish dish(name, label, price, description, icon_address);
            QString qlabel = QString::fromStdString(label);
            std::cout<<qlabel.toInt()<<std::endl;
            DishesMap[qlabel.toInt()].push_back(dish);
        }
        inFile.close();
    }
}

void DishesMapOperator::clearFile() {
    // clear the file to the empty state
    // 以截断模式打开文件，这会清除文件的所有内容
    std::ofstream outFile(filename, std::ios::trunc);
    if (outFile.is_open()) {
        outFile.close();
    }
}

void DishesMapOperator::printAllDishes() const {
    std::cout << "All Dishes:\n";
    for (const auto& pair : DishesMap) {
        for (const auto& dish : pair.second) {
            std::cout << "Name: " << dish.getName() << ", Label: " << dish.getLabel() << ", Price: " << dish.getPrice() << ", Icon Address: " << dish.getIconAddress() << "\n";
        }
    }
}

std::list<std::string> DishesMapOperator::getAllDishesAsList() const {
    std::list<std::string> dishesList; // 用于存储所有的 dish 信息
    for (const auto& pair : DishesMap) {
        for (const auto& dish : pair.second) {
            // 格式化每个 dish 的信息并添加到列表
            std::string dishInfo =  dish.getName();

            dishesList.push_back(dishInfo);
        }
    }
    return dishesList;
}

void DishesMapOperator::testAndPrintQmap() const {
    const QMap<int, QVector<QVector<QString>>> map = this->getQmap();
    qDebug() << "Testing QMap structure:";
    qDebug() << "Total categories:" << map.size();

    // 遍历所有类别（标签）
    for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
        qDebug() << "\nCategory (Label):" << it.key();
        const QVector<QVector<QString>>& dishes = it.value();
        qDebug() << "Number of dishes in this category:" << dishes.size();

        // 遍历该类别下的所有菜品
        for (int i = 0; i < dishes.size(); ++i) {
            const QVector<QString>& dish = dishes[i];
            qDebug() << "\n  Dish" << i + 1 << ":";
            if (dish.size() >= 4) {
                qDebug() << "    Name:" << dish[0];
                qDebug() << "    Price:" << dish[1];
                qDebug() << "    Description:" << dish[2];
                qDebug() << "    Icon Address:" << dish[3];
            } else {
                qDebug() << "    Warning: Incomplete dish data";
            }
        }
    }
    qDebug() << "\nQMap structure test completed.";
}
