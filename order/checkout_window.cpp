#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QFile>
#include <QTextEdit>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <checkout_window.h>
#include <checkoutoperator.h>
#include <OrderOperator.h>
#include <card.h>
#include <waiter.h>
#include <bank.h>
#include <OrderOperator.h>
#include <iostream>
#include "rating_window.h"
class CheckoutInterface : public QWidget {//Honorable Work by Ziqi ZHAO, 122090793
public:

    CheckoutInterface(QString tableNumber, double totalAmount, std::string waiterid ,OrderOperator *oo,QWidget *parent = nullptr ) : QWidget(parent) {
        // 设置窗口大小
        this->resize(1800, 1200);//Honorable Work by Ziqi ZHAO, 122090793

        std::vector<double> disrate = {1.0};
        // 创建网格布局
        QGridLayout *gridLayout = new QGridLayout(this);//Honorable Work by Ziqi ZHAO, 122090793

        // 设置统一样式
        QString buttonStyle = "QPushButton {"//Honorable Work by Ziqi ZHAO, 122090793
                              "border: 2px solid #5A5A5A;"
                              "background-color: #FFFFFF;"
                              "border-radius: 5px;"
                              "padding: 16px 20px;"
                              "font-size: 30px;"
                              "color: #333333;"
                              "font-family: 'Times New Roman';"
                              "} "//Honorable Work by Ziqi ZHAO, 122090793
                              "QPushButton:hover {"
                              "background-color: #f1f1f1;"
                              "} "
                              "QPushButton:pressed {"
                              "background-color: #e0e0e0;"
                              "}";

        QString labelStyle = "QLabel {"//Honorable Work by Ziqi ZHAO, 122090793
                             "font-size: 40px;"
                             "font-weight: bold;"
                             "color: #333333;"
                             "border: 2px solid #5A5A5A;"
                             "padding: 10px;"
                             "margin-bottom: 5px;"//Honorable Work by Ziqi ZHAO, 122090793
                             "border-radius: 5px;"
                             "}";

        QString sublabelStyle = "QLabel {"
                             "font-size: 30px;"
                             "font-weight: bold;"//Honorable Work by Ziqi ZHAO, 122090793
                             "color: #333333;"
                             "padding: 10px;"
                             "margin-bottom: 2px;"
                             "font-family: 'Arial';"//Honorable Work by Ziqi ZHAO, 122090793
                             "}";

        QString titleStyle = "QLabel {"
                             "font-size:50px;"
                             "font-weight: bold;"//Honorable Work by Ziqi ZHAO, 122090793
                             "color: #005f99;"
                             "padding: 10px;"

                             "}";

        // 顶部信息部分（桌号和金额横向排列）//Honorable Work by Ziqi ZHAO, 122090793

        QLabel *tableLabel = new QLabel("Table Number: " + tableNumber);
        tableLabel->setStyleSheet(labelStyle );//Honorable Work by Ziqi ZHAO, 122090793

        QLabel *amountLabel = new QLabel("Total Amount: $" + QString::number(totalAmount));
        amountLabel->setStyleSheet(labelStyle);//Honorable Work by Ziqi ZHAO, 122090793

        QHBoxLayout *topLayout = new QHBoxLayout();//Honorable Work by Ziqi ZHAO, 122090793
        topLayout->addWidget(tableLabel);
        topLayout->addWidget(amountLabel);
        QWidget *topWidget = new QWidget();
        topWidget->setLayout(topLayout);//Honorable Work by Ziqi ZHAO, 122090793
        gridLayout->addWidget(topWidget, 0, 0, 1, 2);

        // 中间点餐信息部分
        QLabel *orderInfoLabel = new QLabel("Order Information");
        orderInfoLabel->setStyleSheet(titleStyle);//Honorable Work by Ziqi ZHAO, 122090793
        gridLayout->addWidget(orderInfoLabel, 1, 0, 1, 2);

        QTextEdit *orderInfoBox = new QTextEdit();//Honorable Work by Ziqi ZHAO, 122090793
        orderInfoBox->setReadOnly(true);
        std::vector<std::vector<std::string>> orders = oo-> getUIInfoWithoutMark();
        QString order_text = "";//Honorable Work by Ziqi ZHAO, 122090793

        // 检查 orders 是否为空
        if (orders.empty()) {//Honorable Work by Ziqi ZHAO, 122090793
            // 如果没有订单，设置提示信息
            order_text = "There is no dish.";  // 或者其他你想显示的提示信息
        } else {//Honorable Work by Ziqi ZHAO, 122090793
            // 遍历 orders 中的每一条订单
            order_text="NO. DISH  QUANTITY  PRICE\n";
            for (size_t i = 0; i < orders.size(); ++i) {
                // 假设每个订单是一个包含菜名、数量和价格等信息的 vector
                const std::vector<std::string>& order = orders[i];//Honorable Work by Ziqi ZHAO, 122090793

                // 检查订单中至少包含 3 个元素（菜名、数量、价格）

                if (order.size() >= 3) {//Honorable Work by Ziqi ZHAO, 122090793
                    QString dish_name = QString::fromStdString(order[0]); // 菜名
                    QString quantity = QString::fromStdString(order[1]);  // 数量
                    QString price = QString::fromStdString(order[2]);     // 价格

                    // 将订单信息格式化并添加到 order_text//Honorable Work by Ziqi ZHAO, 122090793
                    order_text += QString("%1. %2  %3 $%4\n").arg(i + 1).arg(dish_name).arg(quantity).arg(price);
                }
            }
        }

        // 将订单信息显示在 orderInfoBox 中
        orderInfoBox->setText(order_text);//Honorable Work by Ziqi ZHAO, 122090793
        orderInfoBox->setStyleSheet("font-size: 30px; padding: 10px;");
        gridLayout->addWidget(orderInfoBox, 2, 0, 1, 2);//Honorable Work by Ziqi ZHAO, 122090793

        // 支付方式部分
        QLabel *paymentLabel = new QLabel("Choose the Payment");
        paymentLabel->setStyleSheet(sublabelStyle);//Honorable Work by Ziqi ZHAO, 122090793
        gridLayout->addWidget(paymentLabel, 5, 0, 1, 2);

        QHBoxLayout *paymentLayout = new QHBoxLayout();
        QPushButton *payCash = new QPushButton("Cash");//Honorable Work by Ziqi ZHAO, 122090793
        payCash->setStyleSheet(buttonStyle);//Honorable Work by Ziqi ZHAO, 122090793
        QPushButton *payCard = new QPushButton("Bankcard");
        payCard->setStyleSheet(buttonStyle);//Honorable Work by Ziqi ZHAO, 122090793
        QPushButton *paycode = new QPushButton("Wechat/Alipay");
        paycode->setStyleSheet(buttonStyle);//Honorable Work by Ziqi ZHAO, 122090793
        QPushButton *payMember = new QPushButton("Members");
        payMember->setStyleSheet(buttonStyle);

        std::string add="D:\\HUAWEI\\Desktop\\code";//Honorable Work by Ziqi ZHAO, 122090793
        checkoutOperator *coo = new checkoutOperator(    oo,
                                                         add,
                                                         add,
                                                         disrate[0]);

        QObject::connect(paycode, &QPushButton::clicked, [=]() {//Honorable Work by Ziqi ZHAO, 122090793

            std::string qrCodePath = coo->getRandomAlipayQRCode();

                    // 创建 QLabel 用于显示二维码
                    QLabel *qrCodeLabel = new QLabel(this);//Honorable Work by Ziqi ZHAO, 122090793
                    qrCodeLabel->setAlignment(Qt::AlignCenter); // 设置图片居中显示

                    if (!qrCodePath.empty()) {
                        // 将 std::string 转换为 QString//Honorable Work by Ziqi ZHAO, 122090793
                        QString qrCodeFilePath = QString::fromStdString(qrCodePath);

                        // 使用 QPixmap 加载图片
                        QPixmap pixmap(qrCodeFilePath);//Honorable Work by Ziqi ZHAO, 122090793

                        // 如果加载成功，设置 QPixmap 到 QLabel//Honorable Work by Ziqi ZHAO, 122090793
                        if (!pixmap.isNull()) {
                            qrCodeLabel->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio)); // 缩放图片，保持比例
                        } else {
                            qrCodeLabel->setText("Failed to load QR Code.");//Honorable Work by Ziqi ZHAO, 122090793
                        }
                    } else {
                        qrCodeLabel->setText("No QR Code available.");//Honorable Work by Ziqi ZHAO, 122090793
                    }

                    // 直接将控件添加到已有的布局中
                    QGridLayout *gridLayout = qobject_cast<QGridLayout*>(this->layout());
                    if (gridLayout) {//Honorable Work by Ziqi ZHAO, 122090793
                        // 成功获取到 QGridLayout 后，继续添加控件
                        gridLayout->addWidget(qrCodeLabel, 9, 0, 1, 2);  // 根据需要调整位置
                    } else {
                        qDebug() << "Failed to cast layout to QGridLayout";
                    }
                    RatingWindow *rw =new RatingWindow(waiterid);
                    rw->show();
                    oo->clearOrder();//Honorable Work by Ziqi ZHAO, 122090793
                });


        QObject::connect(payCard, &QPushButton::clicked, [=]() {
            PaymentWindow *pw = new PaymentWindow(totalAmount*disrate[0]);//Honorable Work by Ziqi ZHAO, 122090793
            pw->show();
            oo->clearOrder();

        });

        QObject::connect(payCash, &QPushButton::clicked, [=]() {
            // 显示一个输入对话框，要求用户输入收入金额//Honorable Work by Ziqi ZHAO, 122090793
            bool ok;
            double amountPaid = QInputDialog::getDouble(this, "Enter Amount Paid",
                                                        "Enter the amount you received:",
                                                        0, 0, 10000, 2, &ok);

            if (ok) {
                // 计算找零金额//Honorable Work by Ziqi ZHAO, 122090793
                double changeAmount = amountPaid - totalAmount * disrate[0];  // 总金额乘以折扣率
                if (changeAmount >= 0) {//Honorable Work by Ziqi ZHAO, 122090793
                    // 显示找零金额
                    QString message = QString("Amount Paid: $%1\nChange: $%2")
                                      .arg(amountPaid, 0, 'f', 2)
                                      .arg(changeAmount, 0, 'f', 2);
                    QMessageBox::information(this, "Change", message);//Honorable Work by Ziqi ZHAO, 122090793
                    RatingWindow *rw =new RatingWindow(waiterid);
                    rw->show();
                } else {
                    // 如果用户支付的金额小于总金额，提示用户付款不足
                    QMessageBox::warning(this, "Insufficient Payment", "The amount you entered is not enough.");
                }
            }

            oo->clearOrder();
        });//Honorable Work by Ziqi ZHAO, 122090793

        QObject::connect(payMember, &QPushButton::clicked, [=]() {

            double totalCost = oo->getTotalCost() * disrate[0];
            showCardDialog(totalCost);//Honorable Work by Ziqi ZHAO, 122090793
            RatingWindow *rw =new RatingWindow(waiterid);
            rw->show();
            oo->clearOrder();


        });//Honorable Work by Ziqi ZHAO, 122090793
        paymentLayout->addWidget(payCash);//Honorable Work by Ziqi ZHAO, 122090793
        paymentLayout->addWidget(payCard);
        paymentLayout->addWidget(paycode);
        paymentLayout->addWidget(payMember);

        QWidget *paymentWidget = new QWidget();
        paymentWidget->setLayout(paymentLayout);//Honorable Work by Ziqi ZHAO, 122090793
        gridLayout->addWidget(paymentWidget, 6, 0, 1, 2);



        setLayout(gridLayout);
    }
};


