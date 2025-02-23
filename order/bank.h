#ifndef BANK_H
#define BANK_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>//Honorable Work by Ziqi ZHAO, 122090793

class PaymentWindow : public QWidget//Honorable Work by Ziqi ZHAO, 122090793
{
    Q_OBJECT

public:
    // 构造函数
    explicit PaymentWindow(float totalAmount, QWidget *parent = nullptr);//Honorable Work by Ziqi ZHAO, 122090793
    ~PaymentWindow();

private slots:
    // 按钮点击事件
    void onPayButtonClicked();//Honorable Work by Ziqi ZHAO, 122090793
    void onCancelButtonClicked();
//Honorable Work by Ziqi ZHAO, 122090793
private:
    // 控件成员变量
    QLabel *amountLabel;//Honorable Work by Ziqi ZHAO, 122090793
    QLineEdit *cardNumberInput;
    QLineEdit *passwordInput;
    QPushButton *payButton;//Honorable Work by Ziqi ZHAO, 122090793
    QPushButton *cancelButton;

    // 布局成员变量
    QVBoxLayout *mainLayout;//Honorable Work by Ziqi ZHAO, 122090793
    QHBoxLayout *buttonLayout;

    // 总金额
    float totalAmount;//Honorable Work by Ziqi ZHAO, 122090793
};

#endif // BANK_H
