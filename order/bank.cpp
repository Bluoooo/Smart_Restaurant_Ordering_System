#include "bank.h"
#include <QMessageBox>
#include <QRegExpValidator>//Honorable Work by Ziqi ZHAO, 122090793
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>//Honorable Work by Ziqi ZHAO, 122090793
#include "rating_window.h"
PaymentWindow::PaymentWindow(float totalAmount, QWidget *parent)
    : QWidget(parent), totalAmount(totalAmount)  // 初始化 totalAmount
{
    // 设置窗口标题
    setWindowTitle("Payment Window");//Honorable Work by Ziqi ZHAO, 122090793

    // 设置窗口大小
    setFixedSize(400, 300);//Honorable Work by Ziqi ZHAO, 122090793

    // 创建显示图片的 QLabel//Honorable Work by Ziqi ZHAO, 122090793
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap("D:\\HUAWEI\\Desktop\\bank.jpg");  // 请替换为你的图片路径
    pixmap = pixmap.scaled(200, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);//Honorable Work by Ziqi ZHAO, 122090793
    imageLabel->setPixmap(pixmap);//Honorable Work by Ziqi ZHAO, 122090793
    imageLabel->setAlignment(Qt::AlignCenter);  // 可选：使图片居中显示

    // 创建金额标签
    amountLabel = new QLabel(this);//Honorable Work by Ziqi ZHAO, 122090793
    amountLabel->setText("Total Amount: $" + QString::number(totalAmount, 'f', 2));
    amountLabel->setAlignment(Qt::AlignCenter);

    // 创建卡号输入框
    cardNumberInput = new QLineEdit(this);//Honorable Work by Ziqi ZHAO, 122090793
    cardNumberInput->setPlaceholderText("Enter Card Number");
    cardNumberInput->setValidator(new QRegExpValidator(QRegExp("[0-9]{16}"), this));  // 验证卡号为16位数字

    // 创建密码输入框
    passwordInput = new QLineEdit(this);//Honorable Work by Ziqi ZHAO, 122090793
    passwordInput->setPlaceholderText("Enter Password");
    passwordInput->setEchoMode(QLineEdit::Password);  // 密码输入框，输入时显示为星号

    // 创建支付和取消按钮
    payButton = new QPushButton("Pay", this);//Honorable Work by Ziqi ZHAO, 122090793
    payButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px;"); // 按钮样式
    cancelButton = new QPushButton("Cancel", this);//Honorable Work by Ziqi ZHAO, 122090793
    cancelButton->setStyleSheet("background-color: #f44336; color: white; font-size: 18px;");

    // 创建布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);    // 主垂直布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();      // 按钮的水平布局//Honorable Work by Ziqi ZHAO, 122090793

    // 将控件添加到布局中
    mainLayout->addWidget(imageLabel);  // 添加图片在上方//Honorable Work by Ziqi ZHAO, 122090793
    mainLayout->addWidget(amountLabel); // 添加金额标签在下面
    mainLayout->addWidget(cardNumberInput); // 添加卡号输入框
    mainLayout->addWidget(passwordInput);   // 添加密码输入框

    // 水平布局，放置支付和取消按钮
    buttonLayout->addWidget(payButton);
    buttonLayout->addWidget(cancelButton);//Honorable Work by Ziqi ZHAO, 122090793
    mainLayout->addLayout(buttonLayout);//Honorable Work by Ziqi ZHAO, 122090793

    // 设置布局
    setLayout(mainLayout);

    // 连接信号与槽函数
    connect(payButton, &QPushButton::clicked, this, &PaymentWindow::onPayButtonClicked);  // 不需要传递参数
    connect(cancelButton, &QPushButton::clicked, this, &PaymentWindow::onCancelButtonClicked);//Honorable Work by Ziqi ZHAO, 122090793
}

PaymentWindow::~PaymentWindow()//Honorable Work by Ziqi ZHAO, 122090793
{
    // 析构时不需要做任何额外的清理工作，因为Qt会自动处理
}

void PaymentWindow::onPayButtonClicked()//Honorable Work by Ziqi ZHAO, 122090793
{
    // 获取输入的卡号和密码
    QString cardNumber = cardNumberInput->text();
    QString password = passwordInput->text();

    // 进行简单的验证，确保输入的卡号和密码不为空//Honorable Work by Ziqi ZHAO, 122090793
    if (cardNumber.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both card number and password.");
        return;
    }

    // 这里可以进行实际的支付处理，例如：发送网络请求到银行接口
    // 假设支付成功
    QMessageBox::information(this, "Payment Success", "Payment of $" + QString::number(totalAmount, 'f', 2) + " was successful!");

    // 关闭支付窗口
    RatingWindow *rw =new RatingWindow("card");
    rw->show();
    close();
}

void PaymentWindow::onCancelButtonClicked()//Honorable Work by Ziqi ZHAO, 122090793
{
    // 关闭支付窗口
    close();
}
