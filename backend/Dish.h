#ifndef Dish_H
#define Dish_H

#include <string>

class Dish {
public:
    // ??????
    Dish(
        const std::string& name,
        const std::string& label,
        float price,
        const std::string& description = "",
        const std::string& icon_address = "icons/defaultDish.png");

    // ???????
    void setLabel(const std::string& label);
    void setName(const std::string& name);
    void setPrice(float price);
    void setIconAddress(const std::string& icon_address);
    void setDescription(const std::string& description);

    // ??????????????
    std::string getLabel() const;
    std::string getName() const;
    float getPrice() const;
    std::string getIconAddress() const;
    std::string getDescription() const;

private:
    // ???????
    std::string label;
    std::string name;
    std::string icon_address;
    std::string description;
    float price;
};

#endif // Dish_H
