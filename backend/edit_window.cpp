#include "edit_window.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDateTime>
#include <array>
#include <string>
#include <QButtonGroup>
#include <QPalette>
#include <QFont>
#include <QGridLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QListWidget>
#include <QInputDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QList>
#include <QPair>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QComboBox>
#include <QTextEdit>
#include <QTextStream>
#include <QDialogButtonBox>
#include <QDir>
#include <QIcon>
#include <QSpinBox>
#include "Dish.h"
#include "DishesMapOperator.h"
#include <iostream>
edit_window::edit_window()//Honorable Work by Ziqi ZHAO, 122090793
{

}

std::array<QString, 4> sub_menu = {"Main Dish", "Side Dish", "Dessert", "Drink"};//Honorable Work by Ziqi ZHAO, 122090793
 // 应用字体到 QLabel
//Honorable Work by Ziqi ZHAO, 122090793
DishesMapOperator *dmo= new DishesMapOperator ;
//QMap<int, QVector<QVector<QString>>> dishes =dmo->getQmap();
//QMap<int, QVector<QPair<QString, QString>>> dishes = {
//    {0, {{"Steak $55", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Pasta $25", "D:/HUAWEI/Desktop/20241106223100.jpg"},{"Hamburger $35", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Cheeseburger $40", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Beef Noodles $37", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Pizza $60", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Bread $30", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Rice $20", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Chips $25", "D:/HUAWEI/Desktop/20241106223100.jpg"}}},
//    {1, {{"Salad $25", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Fries $7", "D:/HUAWEI/Desktop/20241106223100.jpg"}}},
 //   {2, {{"Cake $20", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Ice Cream $12", "D:/HUAWEI/Desktop/20241106223100.jpg"}}},
//    {3, {{"Soda $8", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Coffee $20", "D:/HUAWEI/Desktop/20241106223100.jpg"}}}
//};//Honorable Work by Ziqi ZHAO, 122090793
QMap<int, QVector<QVector<QString>>> dishes =dmo->getQmap();
//{
//       {0, {{"Steak","55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Pasta","55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"},{"Hamburger","55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Cheeseburger","55","desc1", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Beef Noodles","55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Pizza","55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Bread","$55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Rice","$55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Chips","$55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"}}},
//       {1, {{"Salad","55","desc1", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Fries","55","desc1","D:/HUAWEI/Desktop/20241106223100.jpg"}}},
//       {2, {{"Cake","55","desc1", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Ice Cream","55","desc1", "D:/HUAWEI/Desktop/20241106223100.jpg"}}},
//       {3, {{"Soda","55","desc1", "D:/HUAWEI/Desktop/20241106223100.jpg"}, {"Coffee","55","desc1", "D:/HUAWEI/Desktop/20241106223100.jpg"}}}
//};


void showAddDishDialog(QWidget *parent) {//Honorable Work by Ziqi ZHAO, 122090793
    // 创建对话框
    QDialog *dialog = new QDialog(parent);
    dialog->setWindowTitle("Add New Dish");
    dialog->setFixedSize(400, 350);

    // 创建控件
    QLabel *name_label = new QLabel("Dish Name:");
    QLineEdit *name_edit = new QLineEdit();

    QLabel *price_label = new QLabel("Price:");
    QLineEdit *price_edit = new QLineEdit();

    QLabel *image_label = new QLabel("Image Path:");
    QLineEdit *image_edit = new QLineEdit();

    QLabel *desc_label = new QLabel("Description:");
    QTextEdit *desc_edit = new QTextEdit();

    QLabel *category_label = new QLabel("Category:");//Honorable Work by Ziqi ZHAO, 122090793
    QComboBox *category_combo = new QComboBox();
    category_combo->addItems({"Main Dish", "Side Dish", "Dessert", "Drink"});

    QPushButton *confirm_button = new QPushButton("Confirm");
    QPushButton *cancel_button = new QPushButton("Cancel");//Honorable Work by Ziqi ZHAO, 122090793

    // 布局
    QVBoxLayout *main_layout = new QVBoxLayout(dialog);//Honorable Work by Ziqi ZHAO, 122090793
    main_layout->addWidget(name_label);
    main_layout->addWidget(name_edit);
    main_layout->addWidget(price_label);
    main_layout->addWidget(price_edit);
    main_layout->addWidget(image_label);
    main_layout->addWidget(image_edit);//Honorable Work by Ziqi ZHAO, 122090793
    main_layout->addWidget(desc_label);
    main_layout->addWidget(desc_edit);

    // 添加类别选择
    main_layout->addWidget(category_label);
    main_layout->addWidget(category_combo);//Honorable Work by Ziqi ZHAO, 122090793

    QHBoxLayout *button_layout = new QHBoxLayout();
    button_layout->addWidget(confirm_button);
    button_layout->addWidget(cancel_button);
    main_layout->addLayout(button_layout);//Honorable Work by Ziqi ZHAO, 122090793

    // 按钮功能
    QObject::connect(confirm_button, &QPushButton::clicked, [=]() {
        std::string name_str = name_edit->text().toStdString();
        std::string image_str = image_edit->text().toStdString();//Honorable Work by Ziqi ZHAO, 122090793
        std::string price_str = price_edit->text().toStdString();
        std::string description_str = desc_edit->toPlainText().toStdString();
        std::string category_str = category_combo->currentText().toStdString();
        // 将 price_str 转换为 float
        float price_flo = std::stof(price_str);  // std::stof 会将字符串转换为浮动数,Honorable Work by Ziqi ZHAO, 122090793

        QString name = name_edit->text();
        QString price = price_edit->text();
        QString image = image_edit->text();
        QString description = desc_edit->toPlainText();
        QString category = category_combo->currentText();//Honorable Work by Ziqi ZHAO, 122090793



        // 校验输入Honorable Work by Ziqi ZHAO, 122090793
        if (name.isEmpty() || price.isEmpty() || image.isEmpty() || description.isEmpty()) {
            QMessageBox::warning(dialog, "Input Error", "Please fill in all fields.");
            return;
        }//Honorable Work by Ziqi ZHAO, 122090793

        // 成功处理逻辑（例如打印或保存数据）
        QMessageBox::information(dialog, "Dish Added",
            QString("Dish Name: %1\nPrice: %2\nImage Path: %3\nDescription: %4\nCategory: %5")
            .arg(name, price, image, description, category));
        DishesMapOperator *dmo = new DishesMapOperator();
        dmo->addDish(name_str, category_str,price_flo,description_str,image_str);//Honorable Work by Ziqi ZHAO, 122090793
        dishes =dmo->getQmap();



        dialog->accept(); // 关闭对话框
    });//Honorable Work by Ziqi ZHAO, 122090793

    QObject::connect(cancel_button, &QPushButton::clicked, dialog, &QDialog::reject);

    // 显示对话框
    dialog->exec();//Honorable Work by Ziqi ZHAO, 122090793
}

void showEditDishDialog(QWidget *parent, std::string oldname, int id, int dish_index) {//Honorable Work by Ziqi ZHAO, 122090793
    // 创建对话框
    QDialog *dialog = new QDialog(parent);
    dialog->setWindowTitle("Edit the Dish");//Honorable Work by Ziqi ZHAO, 122090793
    dialog->setFixedSize(500, 350); // 增加宽度以适应按钮布局

    // 创建控件和布局
    QVBoxLayout *main_layout = new QVBoxLayout(dialog);//Honorable Work by Ziqi ZHAO, 122090793

    QString oname =dishes[id][dish_index][0];
    QString oprice =dishes[id][dish_index][1];
    QString odesc =dishes[id][dish_index][2];
    QString oadd =dishes[id][dish_index][3];


    // 创建并布局 Dish Name
    QHBoxLayout *name_layout = new QHBoxLayout();
    QLabel *name_label = new QLabel("Dish Name:");//Honorable Work by Ziqi ZHAO, 122090793
    QLineEdit *name_edit = new QLineEdit();
    name_edit->setPlaceholderText(oname);
    QPushButton *name_confirm_button = new QPushButton("Confirm");
    name_layout->addWidget(name_label);
    name_layout->addWidget(name_edit);//Honorable Work by Ziqi ZHAO, 122090793
    name_layout->addWidget(name_confirm_button);
    main_layout->addLayout(name_layout);//Honorable Work by Ziqi ZHAO, 122090793

    QObject::connect(name_confirm_button, &QPushButton::clicked, [=]() {
        QString name = name_edit->text();//Honorable Work by Ziqi ZHAO, 122090793
        if (name.isEmpty()) {
            QMessageBox::warning(dialog, "Input Error", "Dish name cannot be empty.");
        } else {

            DishesMapOperator *dmo= new DishesMapOperator;
            dmo->updateDishName(oldname ,name.toStdString());//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::information(dialog, "Confirmed", "Dish name updated to: " + name);
            dishes =dmo->getQmap();
            dialog->close();
        }
    });

    // 创建并布局 Price
    QHBoxLayout *price_layout = new QHBoxLayout();//Honorable Work by Ziqi ZHAO, 122090793
    QLabel *price_label = new QLabel("Price:");
    QLineEdit *price_edit = new QLineEdit();
    price_edit->setPlaceholderText(oprice);
    QPushButton *price_confirm_button = new QPushButton("Confirm");
    price_layout->addWidget(price_label);
    price_layout->addWidget(price_edit);//Honorable Work by Ziqi ZHAO, 122090793
    price_layout->addWidget(price_confirm_button);
    main_layout->addLayout(price_layout);

    QObject::connect(price_confirm_button, &QPushButton::clicked, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
        QString price = price_edit->text();
        if (price.isEmpty() || price.toFloat() <= 0) {
            QMessageBox::warning(dialog, "Input Error", "Please enter a valid price.");
        } else {//Honorable Work by Ziqi ZHAO, 122090793
            DishesMapOperator *dmo= new DishesMapOperator;
            dmo->updateDishPrice(oldname ,price.toFloat());//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::information(dialog, "Confirmed", "Price updated to: " + price);
            dishes =dmo->getQmap();
            dialog->close();
        }//Honorable Work by Ziqi ZHAO, 122090793
    });

    // 创建并布局 Image Path
    QHBoxLayout *image_layout = new QHBoxLayout();
    QLabel *image_label = new QLabel("Image Path:");
    QLineEdit *image_edit = new QLineEdit();//Honorable Work by Ziqi ZHAO, 122090793
    image_edit->setPlaceholderText(oadd);
    QPushButton *image_confirm_button = new QPushButton("Confirm");
    image_layout->addWidget(image_label);
    image_layout->addWidget(image_edit);//Honorable Work by Ziqi ZHAO, 122090793
    image_layout->addWidget(image_confirm_button);
    main_layout->addLayout(image_layout);

    QObject::connect(image_confirm_button, &QPushButton::clicked, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
        QString image = image_edit->text();
        if (image.isEmpty()) {
            QMessageBox::warning(dialog, "Input Error", "Image path cannot be empty.");
        } else {
            DishesMapOperator *dmo= new DishesMapOperator;//Honorable Work by Ziqi ZHAO, 122090793
            dmo->updateDishIconAddress(oldname ,image.toStdString());
            QMessageBox::information(dialog, "Confirmed", "Image path updated to: " + image);
            dishes =dmo->getQmap();
            dialog->close();
        }
    });

    // 创建并布局 Description
    QHBoxLayout *desc_layout = new QHBoxLayout();
    QLabel *desc_label = new QLabel("Description:");//Honorable Work by Ziqi ZHAO, 122090793
    QTextEdit *desc_edit = new QTextEdit();
    desc_edit->setPlaceholderText(odesc);
    QPushButton *desc_confirm_button = new QPushButton("Confirm");
    desc_layout->addWidget(desc_label);
    desc_layout->addWidget(desc_edit);
    desc_layout->addWidget(desc_confirm_button);//Honorable Work by Ziqi ZHAO, 122090793
    main_layout->addLayout(desc_layout);

    QObject::connect(desc_confirm_button, &QPushButton::clicked, [=]() {
        QString description = desc_edit->toPlainText();
        if (description.isEmpty()) {//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::warning(dialog, "Input Error", "Description cannot be empty.");
        } else {
            DishesMapOperator *dmo= new DishesMapOperator;
            dmo->updateDishDescription(oldname ,description.toStdString());
            QMessageBox::information(dialog, "Confirmed", "Description updated.");//Honorable Work by Ziqi ZHAO, 122090793
            dishes =dmo->getQmap();
            dialog->close();
        }
    });


    // 显示对话框
    dialog->exec();//Honorable Work by Ziqi ZHAO, 122090793
}


void show_edit_window() {
    // 创建窗口对象（非指针，避免生命周期问题）
    //点单！
    QWidget *order_window = new QWidget;//Honorable Work by Ziqi ZHAO, 122090793
    order_window->setAttribute(Qt::WA_DeleteOnClose); // 关闭窗口时自动释放内存
    order_window->setFixedSize(1200, 1200);  // 设置窗口的尺寸
    order_window->setWindowTitle("Order  Window");
    // 设置字体//Honorable Work by Ziqi ZHAO, 122090793
    QFont buttonFont;
    buttonFont.setFamily("Times New Roman");
    buttonFont.setPointSize(25);
    buttonFont.setBold(true);
//Honorable Work by Ziqi ZHAO, 122090793
    // 创建菜单区域
    QLabel *menu_label = new QLabel(order_window);
    menu_label->setGeometry(100, 150, 1000, 800);//Honorable Work by Ziqi ZHAO, 122090793
    menu_label->setStyleSheet("background-color: white;");

    // 创建菜单标题
    QLabel *menu_title = new QLabel("<p style='font-size:45px; color:black; font-weight: bold;'>MENU EDITOR</p>", order_window);
    menu_title->setGeometry(100, 10, 500, 100);

    // 子菜单


    // 创建子菜单按钮和按钮组//Honorable Work by Ziqi ZHAO, 122090793
    QButtonGroup *sub_menu_buttonGroup = new QButtonGroup(order_window);
    QGridLayout *menu_layout = new QGridLayout(menu_label);

    QVector<QPushButton*> sub_menu_buttons;
    for (int i = 0; i < sub_menu.size(); ++i) {
        QPushButton *button = new QPushButton(sub_menu[i], order_window);
        button->setGeometry(100 + i * 210, 100, 200, 50);//Honorable Work by Ziqi ZHAO, 122090793
        button->setFont(QFont("Times New Roman", 12, QFont::Bold));
        button->setStyleSheet("background-color: lightgray;");
        sub_menu_buttonGroup->addButton(button, i);
        sub_menu_buttons.append(button);
    }//Honorable Work by Ziqi ZHAO, 122090793

    // 动态更新菜单内容
    QObject::connect(sub_menu_buttonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), [=](int id) { // 第 1 层括号开始 (Lambda 捕获)

        // 重置所有按钮的背景颜色
        for (int j = 0; j < 4; ++j) { // 第 2 层括号开始 (for 循环)
            sub_menu_buttons[j]->setStyleSheet("background-color: lightgray;");
        } // 第 2 层括号结束 (for 循环)//Honorable Work by Ziqi ZHAO, 122090793

        // 设置选中的按钮背景颜色//Honorable Work by Ziqi ZHAO, 122090793
        sub_menu_buttons[id]->setStyleSheet("background-color: lightblue;");

        // 清空布局
        QLayoutItem *child;

        while ((child = menu_layout->takeAt(0)) != nullptr) { // 第 2 层括号开始 (while 循环)
            delete child->widget();
            delete child;//Honorable Work by Ziqi ZHAO, 122090793
        } // 第 2 层括号结束 (while 循环)

        // 加载对应分类的菜品
        int row = 0, col = 0;
        int index = 0; // 初始化 index
        QButtonGroup *dish_buttonGroup = new QButtonGroup(menu_label);//Honorable Work by Ziqi ZHAO, 122090793

        for (const auto &dish : dishes[id]) { // 第 2 层括号开始 (for 循环)
            QPushButton *dish_button = new QPushButton(menu_label);
            dish_button->setIcon(QIcon(dish[3]));
            dish_button->setIconSize(QSize(150, 150));
            dish_button->setFixedSize(160, 160);//Honorable Work by Ziqi ZHAO, 122090793

            QString dish_name = QString::fromStdString(dish[0].toStdString());
            QString dish_price = "$" + QString::fromStdString(dish[1].toStdString()); // 菜品价格//Honorable Work by Ziqi ZHAO, 122090793

            QLabel *dish_label = new QLabel(dish_name + "\n" + dish_price, menu_label);
            dish_label->setAlignment(Qt::AlignCenter);
            dish_label->setFont(QFont("Times New Roman", 16));//Honorable Work by Ziqi ZHAO, 122090793

            // 将 id 和 index 打包成 QPair 并存储为按钮的属性
            QPair<int, int> dish_metadata = qMakePair(id, index);
            dish_button->setProperty("dish_metadata", QVariant::fromValue(dish_metadata));//Honorable Work by Ziqi ZHAO, 122090793

            // 将按钮添加到布局和组
            menu_layout->addWidget(dish_button, row, col);
            menu_layout->addWidget(dish_label, row + 1, col);
            dish_buttonGroup->addButton(dish_button);//Honorable Work by Ziqi ZHAO, 122090793

            if (++col == 5) { // 第 3 层括号开始 (if 语句)
                col = 0;
                row += 2;
            } // 第 3 层括号结束 (if 语句)

            ++index; // 更新索引
        } // 第 2 层括号结束 (for 循环)//Honorable Work by Ziqi ZHAO, 122090793

        QObject::connect(dish_buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), [&](QAbstractButton *button) { // 第 1 层括号开始 (Lambda 捕获)

            QPair<int, int> metadata = button->property("dish_metadata").value<QPair<int, int>>();
            int id = metadata.first;
            int dish_index = metadata.second;//Honorable Work by Ziqi ZHAO, 122090793

            // 输出到控制台

            // 弹出窗口让用户选择数量和备注
            // 创建一个新的对话框窗口
            QDialog *dialog = new QDialog(menu_label);
            dialog->setWindowTitle("Dish Selection");//Honorable Work by Ziqi ZHAO, 122090793
            dialog->setFixedSize(550, 300);

            // 创建布局
            QVBoxLayout *layout = new QVBoxLayout(dialog);//Honorable Work by Ziqi ZHAO, 122090793

            // 显示菜品名称和价格
            QString dish_name = QString::fromStdString(dishes[id][dish_index][0].toStdString());//Honorable Work by Ziqi ZHAO, 122090793
            QString dish_price = QString::fromStdString(dishes[id][dish_index][1].toStdString());
            QLabel *label1 = new QLabel("You selected: " + dish_name, dialog);
            label1->setFont(QFont("Times New Roman", 14));//Honorable Work by Ziqi ZHAO, 122090793
            QLabel *label2 = new QLabel("Dish Price is: "+ dish_price, dialog);
            label1->setFont(QFont("Times New Roman", 14));//Honorable Work by Ziqi ZHAO, 122090793
            layout->addWidget(label1);
            layout->addWidget(label2);


            QHBoxLayout *button_layout = new QHBoxLayout();//Honorable Work by Ziqi ZHAO, 122090793
            QPushButton *cancel_button = new QPushButton("Cancel", dialog);//Honorable Work by Ziqi ZHAO, 122090793
            button_layout->addWidget(cancel_button);//Honorable Work by Ziqi ZHAO, 122090793
            QPushButton *edit_button = new QPushButton("Edit Dish", dialog);
            QPushButton *delete_button = new QPushButton("Delete Dish", dialog);
            button_layout->addWidget(edit_button);
            button_layout->addWidget(delete_button);//Honorable Work by Ziqi ZHAO, 122090793
            layout->addLayout(button_layout);

            // 连接按钮信号到槽
            QObject::connect(delete_button, &QPushButton::clicked, dialog, [=]() {
                DishesMapOperator *dmo =new DishesMapOperator();//Honorable Work by Ziqi ZHAO, 122090793
                QMessageBox::information(dialog, "Confirmed", "Successfully deleted " + dishes[id][dish_index][0]);
                dmo->removeDishByName(dishes[id][dish_index][0].toStdString());
                dishes =dmo->getQmap();


                dialog->close();

            });

            QObject::connect(edit_button, &QPushButton::clicked, dialog, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
                showEditDishDialog(dialog, dishes[id][dish_index][0].toStdString(),id,dish_index);

            });


             QObject::connect(cancel_button, &QPushButton::clicked, dialog, &QDialog::reject);

            // 显示对话框
            dialog->exec();//Honorable Work by Ziqi ZHAO, 122090793

        });
        menu_label->setLayout(menu_layout);
    }); // 第 1 层括号结束 (Lambda)

    // 使用 HTML 格式设置分段文字
        menu_label->setStyleSheet("background-color: white;");

        // 创建显示框并设置父对象为窗口
        QLabel *information_label = new QLabel(order_window);
        information_label->setGeometry(1200, 120, 600, 800);  // 设置显示框的位置和大小

        QLabel *information_title = new QLabel(order_window);
        information_title->setGeometry(1200, 65, 500, 50);  // 设置显示框的位置和大小//Honorable Work by Ziqi ZHAO, 122090793

        QPushButton *return_button = new QPushButton("Return", order_window);
        return_button->setGeometry(100, 970, 400, 130);
        return_button->setFont(buttonFont);

        // 返回按钮点击事件
        QObject::connect(return_button, &QPushButton::clicked, [=]() {
            order_window->close();

        });//Honorable Work by Ziqi ZHAO, 122090793

        QPushButton *pic_button = new QPushButton(order_window);
        pic_button->setGeometry(535, 970, 130, 130);//Honorable Work by Ziqi ZHAO, 122090793
        QIcon buttonIcon("D:/HUAWEI/Desktop/menu/CUHK.png");

        pic_button->setIcon(buttonIcon);
        pic_button->setIconSize(QSize(120, 120));  // 设置图标的大小为100x100像素
        pic_button->show();

        QPushButton *add_button = new QPushButton("Add dish", order_window);//Honorable Work by Ziqi ZHAO, 122090793
        add_button->setGeometry(700, 970, 400, 130);  // 设置按钮的位置和大小//Honorable Work by Ziqi ZHAO, 122090793
        add_button->setFont(buttonFont);//Honorable Work by Ziqi ZHAO, 122090793
//Honorable Work by Ziqi ZHAO, 122090793

        QObject::connect(add_button, &QPushButton::clicked, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
            showAddDishDialog(order_window);//Honorable Work by Ziqi ZHAO, 122090793
        });


    // 显示窗口
    order_window->setWindowTitle(QString("Dish Editor"));
    order_window->show();//Honorable Work by Ziqi ZHAO, 122090793
}
