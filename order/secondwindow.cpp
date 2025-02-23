#include "secondwindow.h"
#include <QDebug>
#include <order_window.cpp>
#include <waitTime.h>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>
#include <QWidget>
#include <iostream>
#include <fstream>
#include <string>
#include <ios>
#include <QDateTime>
#include <QScrollArea>  // 添加头文件
#include <QTimer>
QVector<QString> content;

void refreshDialog() {
    content.clear();
    std::ifstream inFile("D:\\HUAWEI\\Desktop\\test_1130\\dialog.txt");
    if (!inFile) {
        std::cerr <<  "Fail to open file "<< std::endl;
    }
    std::string line;
    while (getline(inFile, line)) {
        content.append(QString::fromStdString(line));
    }
    inFile.close();
}

void saveMessage(std::string input) {
    std::ofstream outFile("D:\\HUAWEI\\Desktop\\test_1130\\dialog.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "无法打开文件!" << std::endl;
        return;
    }

    QDateTime Time = QDateTime::currentDateTime();
    QString formattedTime = Time.toString("yyyy-MM-dd HH:mm:ss");
    outFile << std::endl << "Waiters: " << input << "   " << formattedTime.toStdString() << std::endl;
    refreshDialog();
    outFile.close();
}

SecondWindow::SecondWindow(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(1800, 1200); // 设置窗口大小
    setWindowTitle("Order System");
    // 初始化计时器和时间数组
    // 初始化计时器和时间数组
    for (int i = 0; i < 25; ++i) {
        timers[i] = new QTimer(this);
        elapsedTimes[i] = QTime(0, 0, 0); // 初始时间为 00:00:00
        customerNumbers[i] = 0;// 初始化每个桌子的人数为 0
        serverIds[i]="null";

    }

    setupUI();          // 初始化界面
    setupConnections(); // 绑定信号槽
}

SecondWindow::~SecondWindow() {
    for (int i = 0; i < 25; ++i) {
        delete timers[i]; // 删除计时器
    }
}

void SecondWindow::setupUI() {
    centralWidget = new QWidget(this);

    // 创建布局
    layout = new QGridLayout();
    layout->setSpacing(20); // 按钮之间的间距

    // 创建 5x5 的桌子按钮
    for (int i = 0; i < 25; ++i) {
        table_buttons[i] = new QPushButton(QString("Table: %1\nNumber: 0\n00:00:00").arg(i + 1), this);
        table_buttons[i]->setFixedSize(200, 200); // 按钮大小
        table_buttons[i]->setStyleSheet("background-color: green; font-size: 14px; font-weight: bold;");
        layout->addWidget(table_buttons[i], i / 5, i % 5); // 按行列布局
    }

    // 创建右侧 Order Information 区域
    information_title = new QLabel(this);
    information_title->setText("<p style='font-size:40px; color:black; font-weight: bold; font-family: Arial;'>_ _ _ _ _ _ _ _</p>"
                               "<p style='font-size:40px; color:black; font-weight: bold; font-family: Arial;'>TO KITCHEN</p>");

    information_title->setGeometry(1300, 50, 400, 100); // 设置位置和大小

    // 创建信息区域并使用 QScrollArea 来使内容可以滚动//Honorable Work by Ziqi ZHAO, 122090793
        QLabel *information_label = new QLabel(this);
        information_label->setStyleSheet("background-color: lightgray;");
        information_label->setGeometry(1300,180,480,780);//Honorable Work by Ziqi ZHAO, 122090793

        // Create a QScrollArea to make the QLabel scrollable//Honorable Work by Ziqi ZHAO, 122090793
        QScrollArea *scrollArea = new QScrollArea(this);//Honorable Work by Ziqi ZHAO, 122090793
        scrollArea->setWidget(information_label);  // Add the QLabel to the QScrollArea
        scrollArea->setWidgetResizable(true);  // Make the scroll area resizable
        scrollArea->setGeometry(1300, 180, 480, 780);  // Set the geometry for the sc//Honorable Work by Ziqi ZHAO, 122090793rollable area
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);  // Ensure the vertical scroll bar is always visible
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // Disable horizontal scrollbar if not needed//Honorable Work by Ziqi ZHAO, 122090793

    // 创建输入框 QLineEdit (在信息框下方)
        QTimer *timer= new QTimer() ;//Honorable Work by Ziqi ZHAO, 122090793

        // 设置定时器的间隔为 1000 毫秒（1 秒）
        timer->setInterval(500);//Honorable Work by Ziqi ZHAO, 122090793

        // 连接定时器的超时信号到更新函数
        QLabel::connect(timer, &QTimer::timeout, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
            refreshDialog();
            QString displayText;
            for (const QString &str : content) {//Honorable Work by Ziqi ZHAO, 122090793
                displayText += str + "\n";  // Append each QString with a newline
            }
            information_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
            information_label->setText(displayText);  // Set the concatenated text to the label//Honorable Work by Ziqi ZHAO, 122090793

        });

        // 启动定时器
        timer->start();//Honorable Work by Ziqi ZHAO, 122090793
    QLineEdit *input_edit = new QLineEdit(this);//Honorable Work by Ziqi ZHAO, 122090793
    input_edit->setGeometry(1300, 1000, 450, 40); // 设置输入框位置和大小，紧接着信息框的下方
    input_edit->setPlaceholderText("Enter your comment...");//Honorable Work by Ziqi ZHAO, 122090793

    // 创建发送按钮 QPushButton (在输入框下方)//Honorable Work by Ziqi ZHAO, 122090793
    QPushButton *send_button = new QPushButton("Send", this);
    send_button->setGeometry(1300, 1060, 450,100); // 设置按钮位置，紧接着输入框下方

    // 设置按钮的点击事件
    QObject::connect(send_button, &QPushButton::clicked, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
        QString input_text = input_edit->text();  // 获取输入框中的文本
        saveMessage(input_text.toStdString());
        input_edit->clear();//Honorable Work by Ziqi ZHAO, 122090793
    });



    // 设置左侧按钮区域
    QWidget *leftWidget = new QWidget(this);
    leftWidget->setGeometry(50, 50, 1200, 1100);
    leftWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

void SecondWindow::setupConnections() {
    for (int i = 0; i < 25; ++i) {
        connect(table_buttons[i], &QPushButton::clicked, [this, i]() { // 捕获 this 和 i
            // 创建一个输入对话框让用户输入服务员ID
            QInputDialog dialog(this);
            dialog.setWindowTitle("Enter Server ID");
            dialog.setLabelText("Please Enter the Server ID:");

            QString serverId;
            while (true) { // 循环确保用户输入有效
                if (dialog.exec() == QDialog::Accepted) {
                    serverId = dialog.textValue().trimmed(); // 去除前后空格
                    if (serverId.isEmpty()) {
                        QMessageBox::warning(this, "Invalid Input", "Server ID cannot be empty. Please try again.");
                        continue; // 重新弹出输入框
                    }
                    serverIds[i] = serverId.toStdString(); // 保存服务员 ID
                    break; // 输入有效，退出循环
                } else {
                    QMessageBox::information(this, "Operation Canceled", QString("Server ID input canceled for Table: %1").arg(i + 1));
                    return; // 用户取消输入，直接退出
                }
            }

            // 获取输入的顾客人数
            QInputDialog customerDialog(this);
            customerDialog.setWindowTitle("Enter Number of Customers");
            customerDialog.setLabelText("Please Enter the Number of Customers:");
            customerDialog.setIntRange(1, 100); // 顾客人数范围为 1 到 100
            customerDialog.setIntValue(1);

            int customerNumber = 0;
            while (true) { // 循环确保用户输入有效
                if (customerDialog.exec() == QDialog::Accepted) {
                    customerNumber = customerDialog.intValue();
                    if (customerNumber < 1 || customerNumber > 100) { // 冗余校验
                        QMessageBox::warning(this, "Invalid Input", "Customer number must be between 1 and 100. Please try again.");
                        continue; // 重新弹出输入框
                    }
                    customerNumbers[i] = customerNumber; // 保存顾客人数
                    break; // 输入有效，退出循环
                } else {
                    QMessageBox::information(this, "Operation Canceled", QString("Customer input canceled for Table: %1").arg(i + 1));
                    return; // 用户取消输入，直接退出
                }
            }

            // 更新按钮文本（显示桌号、服务员ID和顾客人数）
            std::string basePath = "D:\\HUAWEI\\Desktop\\test_1130\\table_orders";  // 添加基础路径成员变量
            std::string FileName = basePath + "/order_table_" + std::to_string(i+1) + ".txt";
            table_buttons[i]->setText(QString("Table: %1\nServer: %2\nCustomers: %3\n%4")
                                          .arg(i + 1)                // 桌号
                                          .arg(QString::fromStdString(serverIds[i]))         // 服务员ID
                                          .arg(customerNumbers[i])   // 顾客人数
                                          .arg(elapsedTimes[i].toString("hh:mm:ss"))); // 计时信息


            table_buttons[i]->setStyleSheet("background-color: red; font-size: 14px; font-weight: bold;");

            // 如果计时器未启动，启动计时器
            if (!timers[i]->isActive()) {
                connect(timers[i], &QTimer::timeout, [this, i]() { // 捕获 this 和 i
                    elapsedTimes[i] = elapsedTimes[i].addSecs(1);
                    table_buttons[i]->setText(QString("Table: %1\nServer: %2\nCustomers: %3\n%4")
                                                  .arg(i + 1)
                                                  .arg(QString::fromStdString(serverIds[i]))
                                                  .arg(customerNumbers[i])
                                                  .arg(elapsedTimes[i].toString("hh:mm:ss")));

                });
                timers[i]->start(1000); // 每秒触发一次
            }

            // 跳转到 MainWindow
            show_order_window(i + 1, customerNumbers[i], serverIds[i]);
        });
    }
}

