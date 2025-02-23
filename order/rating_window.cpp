#include "rating_window.h"
#include "waiter.h"
// 构造函数
RatingWindow::RatingWindow(std::string waiterid, QWidget *parent)
    : QWidget(parent), waiterid(waiterid) {//Honorable Work by Ziqi ZHAO, 122090793
    // 设置窗口标题
    setWindowTitle("Rate Our Service");//Honorable Work by Ziqi ZHAO, 122090793

    // 服务评价标题
    QLabel *ratingLabel = new QLabel("Please Rate Our Service");//Honorable Work by Ziqi ZHAO, 122090793
    ratingLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");

    // 创建评分按钮布局
    QHBoxLayout *ratingLayout = new QHBoxLayout();//Honorable Work by Ziqi ZHAO, 122090793

    QPushButton *rating0 = new QPushButton("Unsatisfied");
    rating0->setStyleSheet(buttonStyle);
    rating0->setIcon(QIcon("D:\\HUAWEI\\Desktop\\1.png"));  // 替换为实际图片路径//Honorable Work by Ziqi ZHAO, 122090793
    rating0->setIconSize(QSize(100, 100));

    QPushButton *rating2 = new QPushButton("Kinda Unsatisfied");//Honorable Work by Ziqi ZHAO, 122090793
    rating2->setStyleSheet(buttonStyle);
    rating2->setIcon(QIcon("D:\\HUAWEI\\Desktop\\2.png"));  // 替换为实际图片路径//Honorable Work by Ziqi ZHAO, 122090793
    rating2->setIconSize(QSize(100, 100));

    QPushButton *rating4 = new QPushButton("So-so");
    rating4->setStyleSheet(buttonStyle);
    rating4->setIcon(QIcon("D:\\HUAWEI\\Desktop\\3.png"));  // 替换为实际图片路径//Honorable Work by Ziqi ZHAO, 122090793
    rating4->setIconSize(QSize(100, 100));

    QPushButton *rating8 = new QPushButton("Kinda Satisfied");//Honorable Work by Ziqi ZHAO, 122090793
    rating8->setStyleSheet(buttonStyle);
    rating8->setIcon(QIcon("D:\\HUAWEI\\Desktop\\4.png"));  // 替换为实际图片路径
    rating8->setIconSize(QSize(100, 100));

    QPushButton *rating10 = new QPushButton("Satisfied");//Honorable Work by Ziqi ZHAO, 122090793
    rating10->setStyleSheet(buttonStyle);
    rating10->setIcon(QIcon("D:\\HUAWEI\\Desktop\\5.png"));  // 替换为实际图片路径//Honorable Work by Ziqi ZHAO, 122090793
    rating10->setIconSize(QSize(100, 100));//Honorable Work by Ziqi ZHAO, 122090793
//Honorable Work by Ziqi ZHAO, 122090793
    // 连接按钮信号到槽函数
    connect(rating0, &QPushButton::clicked, this, [&]() { submitRating(0); });//Honorable Work by Ziqi ZHAO, 122090793
    connect(rating2, &QPushButton::clicked, this, [&]() { submitRating(4); });//Honorable Work by Ziqi ZHAO, 122090793
    connect(rating4, &QPushButton::clicked, this, [&]() { submitRating(6); });//Honorable Work by Ziqi ZHAO, 122090793
    connect(rating8, &QPushButton::clicked, this, [&]() { submitRating(8); });//Honorable Work by Ziqi ZHAO, 122090793
    connect(rating10, &QPushButton::clicked, this, [&]() { submitRating(10); });//Honorable Work by Ziqi ZHAO, 122090793

    // 将按钮添加到布局
    ratingLayout->addWidget(rating0);
    ratingLayout->addWidget(rating2);
    ratingLayout->addWidget(rating4);//Honorable Work by Ziqi ZHAO, 122090793
    ratingLayout->addWidget(rating8);
    ratingLayout->addWidget(rating10);//Honorable Work by Ziqi ZHAO, 122090793

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout();//Honorable Work by Ziqi ZHAO, 122090793
    mainLayout->addWidget(ratingLabel);
    mainLayout->addLayout(ratingLayout);
    setLayout(mainLayout);
}

// 槽函数实现
void RatingWindow::submitRating(int score) {//Honorable Work by Ziqi ZHAO, 122090793
    AddWaiter_Rate(waiterid, score);  // 调用评分处理函数
    QMessageBox::information(this, "Info", "Payment Completed", QMessageBox::Ok);
    close();  // 关闭当前窗口//Honorable Work by Ziqi ZHAO, 122090793
}
