#include "order_window.h"
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
#include <QSpinBox>
#include "Dish.h"
#include "DishesMapOperator.h"
#include "card.h"
#include "OrderOperator.h"
#include "checkout_window.cpp"
#include <iostream>
order_window::order_window()//Honorable Work by Ziqi ZHAO, 122090793
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


void show_order_window(int table_num, int customer_num, std::string serverid) {
    // 创建窗口对象（非指针，避免生命周期问题）
    //点单！

    OrderOperator *oo = new OrderOperator(table_num, customer_num,serverid, dmo);
    QWidget *order_window = new QWidget;//Honorable Work by Ziqi ZHAO, 122090793
    order_window->setAttribute(Qt::WA_DeleteOnClose); // 关闭窗口时自动释放内存
    order_window->setFixedSize(1800, 1200);  // 设置窗口的尺寸
    order_window->setWindowTitle("Order  Window");
    // 设置字体//Honorable Work by Ziqi ZHAO, 122090793
    QFont buttonFont;
    buttonFont.setFamily("Times New Roman");
    buttonFont.setPointSize(25);
    buttonFont.setBold(true);
//Honorable Work by Ziqi ZHAO, 122090793
    // 创建按钮
    QPushButton *return_button = new QPushButton("Return", order_window);
    return_button->setGeometry(67, 970, 300, 130);//Honorable Work by Ziqi ZHAO, 122090793
    return_button->setFont(buttonFont);

    QPushButton *undo_button = new QPushButton("Delete", order_window);
    undo_button->setGeometry(434, 970, 300, 130);
    undo_button->setFont(buttonFont);//Honorable Work by Ziqi ZHAO, 122090793

    QPushButton *check_out_button = new QPushButton("Check Out", order_window);
    check_out_button->setGeometry(801, 970, 300, 130);//Honorable Work by Ziqi ZHAO, 122090793
    check_out_button->setFont(buttonFont);

    QObject::connect(check_out_button, &QPushButton::clicked, [=]() {
        QString tableNumber = QString::fromStdString(oo->getTableNumber());
        std::cout<<tableNumber.toInt()<<std::endl;//Honorable Work by Ziqi ZHAO, 122090793
        double totalAmount = oo->getTotalCost();
        // Sample total amount
        std::cout<<totalAmount<<std::endl;//Honorable Work by Ziqi ZHAO, 122090793
        std::cout<<serverid<<std::endl;
        // 创建并显示结账界面窗口
        CheckoutInterface *checkoutWindow = new CheckoutInterface(tableNumber, totalAmount, serverid,oo);
        checkoutWindow->update();
        checkoutWindow->setWindowTitle("Check Out Window");
        checkoutWindow->show();


    });//Honorable Work by Ziqi ZHAO, 122090793

    QObject::connect(undo_button, &QPushButton::clicked, [=]() {
        // 创建一个对话框
        QDialog dialog;
        dialog.setWindowTitle("Enter Dish and Quantity");
        QVBoxLayout* layout = new QVBoxLayout(&dialog);//Honorable Work by Ziqi ZHAO, 122090793

        // 添加菜名选择下拉框
        QLabel* labelDish = new QLabel("Select Dish:");
        QComboBox* comboBox = new QComboBox();//Honorable Work by Ziqi ZHAO, 122090793

        // 获取所有菜名并转换为 QStringList
        std::vector<std::vector<std::string>> list = oo->getUIInfoWithoutMark();
        QStringList dishNames;
        for (const auto& dish : list) {
            dishNames.append(QString::fromStdString(dish[0]));  // 将 std::string 转换为 QString 并添加到 QStringList
        }

        comboBox->addItems(dishNames);  // 将转换后的 QStringList 添加到 comboBox
        layout->addWidget(labelDish);
        layout->addWidget(comboBox);

        // 添加数量选择框
        QLabel* labelQuantity = new QLabel("Enter Quantity:");
        QSpinBox* spinBox = new QSpinBox();
        spinBox->setRange(1, 100); // 设置数量范围
        spinBox->setValue(1);      // 设置默认值//Honorable Work by Ziqi ZHAO, 122090793
        layout->addWidget(labelQuantity);
        layout->addWidget(spinBox);

        // 添加确定和取消按钮
        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addWidget(buttonBox);//Honorable Work by Ziqi ZHAO, 122090793

        // 连接按钮信号到对话框槽函数
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);//Honorable Work by Ziqi ZHAO, 122090793

        // 显示对话框并处理结果
        if (dialog.exec() == QDialog::Accepted) {
            QString selectedDish = comboBox->currentText(); // 获取选中的菜名
            int dishQuantity = spinBox->value();       // 获取输入的数量//Honorable Work by Ziqi ZHAO, 122090793

            // 输出结果
            oo->deleteorder(selectedDish.toStdString(),dishQuantity);
            QMessageBox::information(nullptr, "Order Deleted", QString("Dish: %1\nQuantity: %2")
                                                          .arg(selectedDish)
                                                          .arg(dishQuantity));//Honorable Work by Ziqi ZHAO, 122090793
        } else {
            QMessageBox::information(nullptr, "Action Canceled", "No order was deleted.");
        }
    });

    // 创建菜单区域
    QLabel *menu_label = new QLabel(order_window);
    menu_label->setGeometry(100, 150, 1000, 800);//Honorable Work by Ziqi ZHAO, 122090793
    menu_label->setStyleSheet("background-color: white;");

    // 创建菜单标题
    QLabel *menu_title = new QLabel("<p style='font-size:45px; color:black; font-weight: bold;'>MENU</p>", order_window);
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
        button->setStyleSheet("background-color: lightgray;");//Honorable Work by Ziqi ZHAO, 122090793
        sub_menu_buttonGroup->addButton(button, i);
        sub_menu_buttons.append(button);
    }//Honorable Work by Ziqi ZHAO, 122090793

    // 动态更新菜单内容
    QObject::connect(sub_menu_buttonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), [=](int id) { // 第 1 层括号开始 (Lambda 捕获)
        dishes =dmo->getQmap();
        // 重置所有按钮的背景颜色//Honorable Work by Ziqi ZHAO, 122090793
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
            QString dish_name = QString::fromStdString(dishes[id][dish_index][0].toStdString());
            QLabel *label = new QLabel("You selected: " + dish_name, dialog);
            label->setFont(QFont("Times New Roman", 14));//Honorable Work by Ziqi ZHAO, 122090793
            layout->addWidget(label);

            // 数量选择
            QLabel *quantity_label = new QLabel("Quantity:", dialog);
            layout->addWidget(quantity_label);

            QSpinBox *quantity_spinbox = new QSpinBox(dialog);
            quantity_spinbox->setRange(1, 100);//Honorable Work by Ziqi ZHAO, 122090793
            quantity_spinbox->setValue(1);
            layout->addWidget(quantity_spinbox);

            // 用户备注
            QLabel *remark_label = new QLabel("Remarks (e.g., dietary restrictions):", dialog);
            layout->addWidget(remark_label);//Honorable Work by Ziqi ZHAO, 122090793

            QLineEdit *remark_edit = new QLineEdit(dialog);
            remark_edit->setText("NoRemark");  // 设置默认文本
            layout->addWidget(remark_edit);//Honorable Work by Ziqi ZHAO, 122090793

            QHBoxLayout *button_layout = new QHBoxLayout();//Honorable Work by Ziqi ZHAO, 122090793
            QPushButton *confirm_button = new QPushButton("Confirm", dialog);
            QPushButton *cancel_button = new QPushButton("Cancel", dialog);//Honorable Work by Ziqi ZHAO, 122090793
            confirm_button->setStyleSheet("background-color: lightyellow;");  // Add bold red border and light yellow background
            button_layout->addWidget(confirm_button);
            button_layout->addWidget(cancel_button);//Honorable Work by Ziqi ZHAO, 122090793
            layout->addLayout(button_layout);


            QObject::connect(confirm_button, &QPushButton::clicked, dialog, [=]() {
                int quantity = quantity_spinbox->value();
                QString remarks = remark_edit->text();//Honorable Work by Ziqi ZHAO, 122090793

                // 输出选择的信息
                std::cout << "Dish: " << dishes[id][dish_index][0].toStdString()
                          << ", Quantity: " << quantity
                          << ", Remarks: " << remarks.toStdString() << std::endl;
                oo->addorder(dish_name.toStdString(),quantity,remarks.toStdString());
                std::vector<std::vector<std::string>> orders = oo->getUIInfo();
                QString order_text = "NO.  DISH  QUANTITY PRICE REMARK\n";

                // 检查 orders 是否为空
                if (orders.empty()) {
                    // 如果没有订单，设置提示信息
                    order_text += "There is no dish.";  // 或者其他你想显示的提示信息
                } else {//Honorable Work by Ziqi ZHAO, 122090793
                    // 遍历 orders 中的每一条订单
                    for (size_t i = 0; i < orders.size(); ++i) {//Honorable Work by Ziqi ZHAO, 122090793
                        // 假设每个订单是一个包含菜名、数量和价格等信息的 vector
                        const std::vector<std::string>& order = orders[i];

                        // 检查订单中至少包含 3 个元素（菜名、数量、价格）
                        order_text="NO. DISH  QUANTITY  PRICE\n";
                        if (order.size() >= 3) {//Honorable Work by Ziqi ZHAO, 122090793
                            QString dish_name = QString::fromStdString(order[0]); // 菜名
                            QString quantity = QString::fromStdString(order[1]);  // 数量
                            QString price = QString::fromStdString(order[2]);  // 价格
                            QString remark = QString::fromStdString(order[3]);  //备注//Honorable Work by Ziqi ZHAO, 122090793


                            // 将订单信息格式化并添加到 order_text
                            order_text += QString("%1. %2  %3 $%4 %5\n").arg(i + 1).arg(dish_name).arg(quantity).arg(price).arg(remark);
                        }//Honorable Work by Ziqi ZHAO, 122090793
                    }

                };


                dialog->accept();//Honorable Work by Ziqi ZHAO, 122090793
            });

             QObject::connect(cancel_button, &QPushButton::clicked, dialog, &QDialog::reject);//Honorable Work by Ziqi ZHAO, 122090793

            // 显示对话框
            dialog->exec();//Honorable Work by Ziqi ZHAO, 122090793

        });
        menu_label->setLayout(menu_layout);
    }); // 第 1 层括号结束 (Lambda)













    // 返回按钮点击事件
    QObject::connect(return_button, &QPushButton::clicked, [=]() {
        order_window->close();

    });//Honorable Work by Ziqi ZHAO, 122090793

    // 使用 HTML 格式设置分段文字
        menu_label->setStyleSheet("background-color: white;");

        // 创建显示框并设置父对象为窗口
        QLabel *information_label = new QLabel(order_window);
        information_label->setGeometry(1200, 120, 600, 800);  // 设置显示框的位置和大小

        QLabel *information_title = new QLabel(order_window);
        information_title->setGeometry(1200, 65, 500, 50);  // 设置显示框的位置和大小//Honorable Work by Ziqi ZHAO, 122090793


        // 创建左上角显示座位号的 QLabel
        QLabel *seat_label = new QLabel(order_window);
        seat_label->setGeometry(1200, 50, 100, 80); // 左上角

        // 使用 QString 动态插入 table_num//Honorable Work by Ziqi ZHAO, 122090793
        QString seat_text = QString("<p style='font-size:50px; color:black; font-weight: bold;'>%1</p>").arg(table_num);
        seat_label->setText(seat_text);

        // 设置背景样式
        seat_label->setStyleSheet("background-color: white; padding: 5px;");

         // 创建顶部偏右显示人数和时间的 QLabel
         QLabel *info_label = new QLabel(order_window);//Honorable Work by Ziqi ZHAO, 122090793
         info_label->setGeometry(1400, 50, 300, 80); // 顶部偏右
         QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
         QString info_text = QString("<p style='font-size:25px; color:green;'>Number:%1</p>"
                                      "<p style='font-size:20px; color:black;'>Time：%2</p>")
                                 .arg(customer_num)
                                 .arg(current_time);//Honorable Work by Ziqi ZHAO, 122090793
         info_label->setText(info_text);
         info_label->setStyleSheet("background-color:white; padding: 5px;");

         // 创建下方显示点单内容的 QLabel
         QLabel *order_label = new QLabel(order_window);
         order_label->setGeometry(1200, 150, 500, 950); // 底部


         QTimer *timer = new QTimer(order_window);
         // 设置定时器的间隔为 1000 毫秒（1 秒）//Honorable Work by Ziqi ZHAO, 122090793
         timer->setInterval(500);

         // 连接定时器的超时信号到更新函数
         QLabel::connect(timer, &QTimer::timeout, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
             // 获取订单信息并更新界面
             std::vector<std::vector<std::string>> orders = oo->getUIInfo();
             QString order_text = "NO.   DISH   QUANTITY   PRICE   REMARK\n";//Honorable Work by Ziqi ZHAO, 122090793

             if (orders.empty()) {
                 order_text += "There is no dish.";//Honorable Work by Ziqi ZHAO, 122090793
             } else {
                 for (size_t i = 0; i < orders.size(); ++i) {
                     const std::vector<std::string> &order = orders[i];//Honorable Work by Ziqi ZHAO, 122090793

                     if (order.size() >= 4) {  // 确保订单包含至少 4 个元素
                         QString dish_name = QString::fromStdString(order[0]); // 菜名
                         QString quantity = QString::fromStdString(order[1]);  // 数量
                         QString price = QString::fromStdString(order[2]);     // 价格//Honorable Work by Ziqi ZHAO, 122090793
                         QString remark = QString::fromStdString(order[3]);    // 备注

                         order_text += QString("%1.    %2    %3   $%4  %5\n")
                                           .arg(i + 1)
                                           .arg(dish_name)
                                           .arg(quantity)//Honorable Work by Ziqi ZHAO, 122090793
                                           .arg(price)
                                           .arg(remark);//Honorable Work by Ziqi ZHAO, 122090793
                     }
                 }
             }

             order_label->setText(order_text);
             order_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);//Honorable Work by Ziqi ZHAO, 122090793
             order_label->setStyleSheet("background-color: white; padding: 10px;");
             order_label->setFont(QFont("Arial", 10, QFont::Bold));//Honorable Work by Ziqi ZHAO, 122090793
         });

         // 启动定时器
         timer->start();

        QObject::connect(return_button, &QPushButton::clicked, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
            order_window->close();//Honorable Work by Ziqi ZHAO, 122090793


        });

    // 显示窗口
    order_window->setWindowTitle(QString("Table %1 - Order Window").arg(table_num));
    order_window->show();//Honorable Work by Ziqi ZHAO, 122090793
}
