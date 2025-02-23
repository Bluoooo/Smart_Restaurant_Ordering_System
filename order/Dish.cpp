#include "Dish.h"

// 构造函数的实现
Dish::Dish(
    const std::string& name,
    const std::string& label,
    float price,
    const std::string& description ,
    const std::string& icon_address)
    : name(name), label(label), price(price), description(description), icon_address(icon_address) {}

// 成员函数的实现
void Dish::setLabel(const std::string& label) {
    this->label = label;
}

void Dish::setName(const std::string& name) {
    this->name = name;
}

void Dish::setPrice(float price) {
    this->price = price;
}

void Dish::setIconAddress(const std::string& icon_address) {
    this->icon_address = icon_address;
}

void Dish::setDescription(const std::string& description) {
    this->description = description;
}

// 成员函数获取变量的实现
std::string Dish::getLabel() const {
    return label;
}

std::string Dish::getName() const {
    return name;
}

float Dish::getPrice() const {
    return price;
}

std::string Dish::getIconAddress() const {
    return icon_address;
}

std::string Dish::getDescription() const {
    return description;
}
