#include <QApplication>//Honorable Work by Ziqi ZHAO, 122090793
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>//Honorable Work by Ziqi ZHAO, 122090793
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>//Honorable Work by Ziqi ZHAO, 122090793
#include "chef.cpp"
#include "edit_window.cpp"
void show_ui0() {

    // 创建主窗口
    QWidget *ui0_window = new QWidget;
    ui0_window->setWindowTitle("CSC3002 Ordering System");
    ui0_window->resize(500, 300);//Honorable Work by Ziqi ZHAO, 122090793

    // 创建标题标签
    QLabel *titleLabel = new QLabel("Please Choose Your Identification", ui0_window);
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
    QPushButton *leftButton = new QPushButton("Chef Workbench", ui0_window);
    leftButton->setMinimumSize(200, 60); // 增大按钮尺寸//Honorable Work by Ziqi ZHAO, 122090793
    leftButton->setStyleSheet(
        "QPushButton {"
        "font-family: 'Times New Roman';"   // 字体设置//Honorable Work by Ziqi ZHAO, 122090793
        "    font-size: 18px;"          // 字体大小增大
        "    font-weight: bold;"        // 字体加粗
        "    color: white;"             // 字体颜色//Honorable Work by Ziqi ZHAO, 122090793
        "    background-color: #0078D7;" // 默认背景颜色
        "    border: none;"             // 无边框
        "    border-radius: 12px;"      // 圆角半径
        "    padding: 12px;"            // 增大内间距//Honorable Work by Ziqi ZHAO, 122090793
        "}"
        "QPushButton:hover {"
        "    background-color: #005BB5;" // 鼠标悬停颜色
        "}"
        "QPushButton:pressed {"
        "    background-color: #004494;" // 按下颜色//Honorable Work by Ziqi ZHAO, 122090793
        "}"
    );

    QPushButton *rightButton = new QPushButton("Dish Editor", ui0_window);//Honorable Work by Ziqi ZHAO, 122090793
    rightButton->setMinimumSize(200, 60); // 与左侧按钮保持一致
    rightButton->setStyleSheet(
        "QPushButton {"
        "font-family: 'Times New Roman';"   // 字体设置
        "    font-size: 18px;"          // 字体大小增大
        "    font-weight: bold;"        // 字体加粗//Honorable Work by Ziqi ZHAO, 122090793
        "    color: white;"             // 字体颜色
        "    background-color: #28A745;" // 默认背景颜色
        "    border: none;"             // 无边框//Honorable Work by Ziqi ZHAO, 122090793
        "    border-radius: 12px;"      // 圆角半径
        "    padding: 12px;"            // 增大内间距
        "}"
        "QPushButton:hover {"
        "    background-color: #218838;" // 鼠标悬停颜色
        "}"
        "QPushButton:pressed {"
        "    background-color: #1E7E34;" // 按下颜色//Honorable Work by Ziqi ZHAO, 122090793
        "}"
    );

    // 布局：水平布局放置两个按钮，居中对齐
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setSpacing(40); // 增大按钮间距//Honorable Work by Ziqi ZHAO, 122090793
    buttonLayout->addStretch();
    buttonLayout->addWidget(leftButton);//Honorable Work by Ziqi ZHAO, 122090793
    buttonLayout->addWidget(rightButton);
    buttonLayout->addStretch();//Honorable Work by Ziqi ZHAO, 122090793

    // 布局：垂直布局放置标题和按钮布局
    QVBoxLayout *mainLayout = new QVBoxLayout(ui0_window);
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(20); // 标题与按钮的间距
    mainLayout->addLayout(buttonLayout);//Honorable Work by Ziqi ZHAO, 122090793
    mainLayout->setContentsMargins(20, 20, 20, 20); // 设置内边距


    // 设置主窗口布局
    ui0_window->setLayout(mainLayout);

    // 显示主窗口
    ui0_window->show();

    QObject::connect(rightButton, &QPushButton::clicked, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
        show_edit_window();
        });//Honorable Work by Ziqi ZHAO, 122090793

    QObject::connect(leftButton, &QPushButton::clicked, [=]() {//Honorable Work by Ziqi ZHAO, 122090793
        setupChefInterface();
        });//Honorable Work by Ziqi ZHAO, 122090793
}






