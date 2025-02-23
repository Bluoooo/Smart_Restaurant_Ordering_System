// EmployeeQueryWindow.cpp
#include "waiter_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <secondwindow.h>
#include <waiter.h>//Honorable Work by Ziqi ZHAO, 122090793
EmployeeQueryWindow::EmployeeQueryWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Performance Searching");
    setFixedSize(600, 400);//Honorable Work by Ziqi ZHAO, 122090793

    // 创建控件
    QLabel *idLabel = new QLabel("Please enter the waiter's ID:", this);
    idLabel->setStyleSheet("font-size: 16px; color: #333;");

    idInput = new QLineEdit(this);
    idInput->setPlaceholderText("Please enter the waiter's ID:");//Honorable Work by Ziqi ZHAO, 122090793
    idInput->setStyleSheet("padding: 10px; font-size: 14px; border: 1px solid #ccc; border-radius: 5px;");

    queryButton = new QPushButton("Search", this);
    queryButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px;");

    resultsTable = new QTableWidget(this);//Honorable Work by Ziqi ZHAO, 122090793
    resultsTable->setColumnCount(4); // 假设显示员工ID, 姓名, 部门
    resultsTable->setHorizontalHeaderLabels({"Waiter ID", "Average Rate Performance", "Grade","Salary"});
    resultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resultsTable->horizontalHeader()->setStretchLastSection(true);//Honorable Work by Ziqi ZHAO, 122090793
    resultsTable->setStyleSheet("QTableWidget { border: 1px solid #ccc; font-size: 14px; }");

    backButton = new QPushButton("Return", this);
    backButton->setStyleSheet("background-color: #f44336; color: white; padding: 10px; border-radius: 5px;");

    // 布局//Honorable Work by Ziqi ZHAO, 122090793
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(idLabel);
    inputLayout->addWidget(idInput);
//Honorable Work by Ziqi ZHAO, 122090793
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(queryButton);
    mainLayout->addWidget(resultsTable);
    mainLayout->addWidget(backButton);//Honorable Work by Ziqi ZHAO, 122090793

    // 信号与槽
    connect(queryButton, &QPushButton::clicked, [this]() {
        QString waiterId = idInput->text();
        if (waiterId.isEmpty()) {//Honorable Work by Ziqi ZHAO, 122090793
            // 如果输入为空，弹出警告框提示
            QMessageBox::warning(this, "Warning", "Waiter's ID cannot be empty！");
            return;
        }

        // 检查文件中是否包含该服务员 ID//Honorable Work by Ziqi ZHAO, 122090793
        bool found = false;
        std::ifstream file("D:\\Users\\HUAWEI\\CLionProjects\\untitled\\CSC3002\\waiter");  // 文件路径
        if (!file.is_open()) {//Honorable Work by Ziqi ZHAO, 122090793
            std::cout << "Unable to open" << filename << std::endl;

        }
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string Waiter_Number;//Honorable Work by Ziqi ZHAO, 122090793
            getline(ss,Waiter_Number,',');  // 获取每行第一个逗号前的ID
            if (QString::fromStdString(Waiter_Number) == waiterId) {
                found = true;//Honorable Work by Ziqi ZHAO, 122090793
                break;
            }
        }

        file.close();

        if (!found) {//Honorable Work by Ziqi ZHAO, 122090793
            // 如果没有找到，弹出提示框并让用户重新输入
            QMessageBox::warning(this, "Not Found", "Waiter ID not found! Please search again.");
            return;  // 退出当前操作，等待用户重新输入//Honorable Work by Ziqi ZHAO, 122090793
        }

        // 假设查询结果，填充数据到表格中
        // 示例数据
        std::vector<std::string> result_vector = waitor_example(waiterId.toStdString());
        if (result_vector.empty()) {//Honorable Work by Ziqi ZHAO, 122090793
            // 如果查询没有返回有效数据，提示错误//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::warning(this, "Error", "No data found for the waiter.");
            return;
        }

        // 如果查询成功，更新表格显示数据
        resultsTable->setRowCount(1);//Honorable Work by Ziqi ZHAO, 122090793
        resultsTable->setItem(0, 0, new QTableWidgetItem(waiterId));
        resultsTable->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(result_vector[1])));
        resultsTable->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(result_vector[2])));
        resultsTable->setItem(0, 3, new QTableWidgetItem(QString::fromStdString(result_vector[3])));//Honorable Work by Ziqi ZHAO, 122090793
    });


    connect(backButton, &QPushButton::clicked, [this]() {
        this->close();  // 关闭当前窗口
        // 创建主窗口
        QWidget *ui0_window = new QWidget;
        ui0_window->setWindowTitle("CSC3002 Ordering System");
        ui0_window->resize(500, 300);//Honorable Work by Ziqi ZHAO, 122090793

        // 创建标题标签
        QLabel *titleLabel = new QLabel("Welcome to CSC3002 Ordering System", ui0_window);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet(//Honorable Work by Ziqi ZHAO, 122090793
            "font-family: 'Times New Roman';"   // 字体设置
            "font-size: 42px;"                 // 字体大小
            "font-weight: bold;"               // 字体加粗
            "color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
            "stop:0 #ff7e5f, stop:1 #feb47b);" // 渐变色，珊瑚橙
            "padding: 10px;"                   // 内间距增加//Honorable Work by Ziqi ZHAO, 122090793
        );


        // 创建左侧按钮
        QPushButton *leftButton = new QPushButton("Waiter's Workbench", ui0_window);
        leftButton->setMinimumSize(200, 60); // 增大按钮尺寸
        leftButton->setStyleSheet(//Honorable Work by Ziqi ZHAO, 122090793
            "QPushButton {"
            "font-family: 'Times New Roman';"   // 字体设置
            "    font-size: 18px;"          // 字体大小增大
            "    font-weight: bold;"        // 字体加粗//Honorable Work by Ziqi ZHAO, 122090793
            "    color: white;"             // 字体颜色
            "    background-color: #0078D7;" // 默认背景颜色
            "    border: none;"             // 无边框//Honorable Work by Ziqi ZHAO, 122090793
            "    border-radius: 12px;"      // 圆角半径
            "    padding: 12px;"            // 增大内间距
            "}"
            "QPushButton:hover {"
            "    background-color: #005BB5;" // 鼠标悬停颜色
            "}"
            "QPushButton:pressed {"
            "    background-color: #004494;" // 按下颜色//Honorable Work by Ziqi ZHAO, 122090793
            "}"
        );

        QPushButton *rightButton = new QPushButton("Ordering System", ui0_window);
        rightButton->setMinimumSize(200, 60); // 与左侧按钮保持一致
        rightButton->setStyleSheet(
            "QPushButton {"
            "font-family: 'Times New Roman';"   // 字体设置
            "    font-size: 18px;"          // 字体大小增大
            "    font-weight: bold;"        // 字体加粗//Honorable Work by Ziqi ZHAO, 122090793
            "    color: white;"             // 字体颜色
            "    background-color: #28A745;" // 默认背景颜色
            "    border: none;"             // 无边框
            "    border-radius: 12px;"      // 圆角半径//Honorable Work by Ziqi ZHAO, 122090793
            "    padding: 12px;"            // 增大内间距
            "}"
            "QPushButton:hover {"
            "    background-color: #218838;" // 鼠标悬停颜色
            "}"
            "QPushButton:pressed {"
            "    background-color: #1E7E34;" // 按下颜色
            "}"
        );

        // 布局：水平布局放置两个按钮，居中对齐
        QHBoxLayout *buttonLayout = new QHBoxLayout;//Honorable Work by Ziqi ZHAO, 122090793
        buttonLayout->setSpacing(40); // 增大按钮间距
        buttonLayout->addStretch();
        buttonLayout->addWidget(leftButton);//Honorable Work by Ziqi ZHAO, 122090793
        buttonLayout->addWidget(rightButton);
        buttonLayout->addStretch();//Honorable Work by Ziqi ZHAO, 122090793

        // 布局：垂直布局放置标题和按钮布局
        QVBoxLayout *mainLayout = new QVBoxLayout(ui0_window);
        mainLayout->addWidget(titleLabel);//Honorable Work by Ziqi ZHAO, 122090793
        mainLayout->addSpacing(20); // 标题与按钮的间距
        mainLayout->addLayout(buttonLayout);
        mainLayout->setContentsMargins(20, 20, 20, 20); // 设置内边距//Honorable Work by Ziqi ZHAO, 122090793


        // 设置主窗口布局
        ui0_window->setLayout(mainLayout);//Honorable Work by Ziqi ZHAO, 122090793

        // 显示主窗口
        ui0_window->show();//Honorable Work by Ziqi ZHAO, 122090793

        QObject::connect(rightButton, &QPushButton::clicked, [=]() {
            SecondWindow *sw= new SecondWindow;
            ui0_window->close();
            sw->show();//Honorable Work by Ziqi ZHAO, 122090793
            });

        QObject::connect(leftButton, &QPushButton::clicked, [=]() {
            ui0_window->close();
            EmployeeQueryWindow *eqw= new EmployeeQueryWindow;
            eqw->show();//Honorable Work by Ziqi ZHAO, 122090793
            });
    });
}

EmployeeQueryWindow::~EmployeeQueryWindow() {
    // 清理资源（如果有的话）
}
