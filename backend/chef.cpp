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
#include <QTimer>
#include <QScrollArea>  // 添加头文件

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

void chef(std::string input) {
    std::ofstream outFile("D:\\HUAWEI\\Desktop\\test_1130\\dialog.txt", std::ios::app);
    if (!outFile) {
        std::cerr << "无法打开文件!" << std::endl;
        return;
    }

    QDateTime Time = QDateTime::currentDateTime();
    QString formattedTime = Time.toString("yyyy-MM-dd HH:mm:ss");
    outFile << std::endl << "Chef: " << input << "   " << formattedTime.toStdString() << std::endl;
    refreshDialog();
    outFile.close();
}

void setupChefInterface() {
    // 创建窗口
    QWidget *window = new QWidget;
    window->setGeometry(100, 100, 600, 800);  // 设置适合手机屏幕的窗口大小
    window->setWindowTitle("Chef Interface");

    // 创建主垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(window);

    // 创建顶部的水平布局（用于放置标题和按钮）
    QHBoxLayout *topLayout = new QHBoxLayout();

    // 创建标题部分
    QLabel *information_title = new QLabel(window);
    information_title->setText("<p style='font-size:40px; color:black; font-weight: bold; font-family: Arial;'>_ _ _ _ _ _ _ _</p>"
                               "<p style='font-size:40px; color:black; font-weight: bold; font-family: Arial;'>TO WAITERS</p>");
    topLayout->addWidget(information_title);  // 将标题放到左侧

    // 创建信息区域并使用 QScrollArea 来使内容可以滚动
    QLabel *information_label = new QLabel(window);
    information_label->setStyleSheet("background-color: lightgray;");
    information_label->setAlignment(Qt::AlignTop);

    // 让 QLabel 的高度适应内容，而不是固定高度
    information_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // 创建一个 QScrollArea 并将 QLabel 放入其中
    QScrollArea *scrollArea = new QScrollArea(window);
    scrollArea->setWidget(information_label);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);  // 将 QScrollArea 添加到布局

    // 创建定时器
    QTimer *timer = new QTimer(window);
    timer->setInterval(500); // 设置定时器的间隔为 500 毫秒

    // 连接定时器的超时信号到更新函数
    QObject::connect(timer, &QTimer::timeout, [=]() {
        refreshDialog();
        QString displayText;
        for (const QString &str : content) {
            displayText += str + "\n";  // 将每个字符串追加为新的一行
        }
        information_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        information_label->setText(displayText);
    });

    // 启动定时器
    timer->start();

    // 添加顶部布局到主布局
    mainLayout->addLayout(topLayout);

    // 创建输入框
    QLineEdit *input_edit = new QLineEdit(window);
    input_edit->setPlaceholderText("Enter your comment...");
    input_edit->setFixedHeight(40);
    mainLayout->addWidget(input_edit);

    // 创建发送按钮
    QPushButton *send_button = new QPushButton("Send", window);
    send_button->setFixedHeight(40);
    mainLayout->addWidget(send_button);

    // 设置按钮的点击事件
    QObject::connect(send_button, &QPushButton::clicked, [=]() {
        QString input_text = input_edit->text();
        content.append(input_text);  // 将用户输入添加到内容中
        chef(input_text.toStdString());
        refreshDialog();
        QString displayText;
        for (const QString &str : content) {
            displayText += str + "\n";
        }
        information_label->setText(displayText);
        input_edit->clear();
    });

    // 设置布局
    window->setLayout(mainLayout);

    // 显示窗口
    window->show();

    // 初始化显示内容
    refreshDialog();
    QString displayText;
    for (const QString &str : content) {
        displayText += str + "\n";
    }
    information_label->setText(displayText);
}
