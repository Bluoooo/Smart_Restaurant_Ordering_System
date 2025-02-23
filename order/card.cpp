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
#include <QTextStream>
#include <QDir>
#include "secondwindow.h"
#include "Dish.h"
#include "DishesMapOperator.h"
// 定义会员卡信息结构
struct MemberCard {//Honorable Work by Ziqi ZHAO, 122090793
    QString name;
    QString phone;
    double balance;//Honorable Work by Ziqi ZHAO, 122090793
};
// 定义数据库文件路径
const QString databaseFile = "E:\\CSC3002\\Proj\\test\\card_information";//Honorable Work by Ziqi ZHAO, 122090793

// 初始化会员卡列表
QList<MemberCard> memberCardList;
//Honorable Work by Ziqi ZHAO, 122090793
// 从文件读取会员卡列表
void readMemberCardListFromFile(const QString &fileName, QList<MemberCard> &list) {
    QFile file(fileName);//Honorable Work by Ziqi ZHAO, 122090793
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file for reading:" << fileName;
        return;//Honorable Work by Ziqi ZHAO, 122090793
    }

    QTextStream in(&file);
    list.clear();//Honorable Work by Ziqi ZHAO, 122090793
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');//Honorable Work by Ziqi ZHAO, 122090793
        if (parts.size() == 3) {
            QString name = parts[0].trimmed();
            QString phone = parts[1].trimmed();//Honorable Work by Ziqi ZHAO, 122090793
            double balance = parts[2].trimmed().toDouble();
            list.append({name, phone, balance});//Honorable Work by Ziqi ZHAO, 122090793
        }
    }
    file.close();
}

// 将会员卡列表写入文件//Honorable Work by Ziqi ZHAO, 122090793
void writeMemberCardListToFile(const QString &fileName, const QList<MemberCard> &list) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Could not open file for writing:" << fileName;
        return;//Honorable Work by Ziqi ZHAO, 122090793
    }

    QTextStream out(&file);
    for (const auto &card : list) {
        out << card.name << "," << card.phone << "," << QString::number(card.balance, 'f', 2) << "\n";//Honorable Work by Ziqi ZHAO, 122090793
    }

    out.flush(); // 强制刷新缓冲区
    file.close();//Honorable Work by Ziqi ZHAO, 122090793
    qDebug() << "Database successfully written to:" << fileName;
}

// 在程序启动时加载数据库
void initializeDatabase() {//Honorable Work by Ziqi ZHAO, 122090793
    readMemberCardListFromFile(databaseFile, memberCardList);
}

// 在程序操作后保存数据库
void updateDatabase() {//Honorable Work by Ziqi ZHAO, 122090793
    writeMemberCardListToFile(databaseFile, memberCardList);
}


void showCardDialog(double total_amount) {
    // 创建新窗口 (QDialog)
    QDialog *cardDialog = new QDialog;//Honorable Work by Ziqi ZHAO, 122090793
    cardDialog->setWindowTitle("Membership Card Checkout");
    cardDialog->setFixedSize(600, 500);

    // 创建布局
    QVBoxLayout *layout = new QVBoxLayout(cardDialog);//Honorable Work by Ziqi ZHAO, 122090793

    // 显示结账金额的标签
    QString amountLabelStr = QString("Total Amount: $%1").arg(total_amount, 0, 'f', 2);

    // 创建 QLabel 并设置文本和样式
    QLabel *amountLabel = new QLabel(amountLabelStr, cardDialog);//Honorable Work by Ziqi ZHAO, 122090793
    amountLabel->setFont(QFont("Times New Roman", 18, QFont::Bold));
    layout->addWidget(amountLabel);//Honorable Work by Ziqi ZHAO, 122090793
    // 搜索框和搜索按钮
    QLineEdit *searchLineEdit = new QLineEdit(cardDialog);//Honorable Work by Ziqi ZHAO, 122090793
    searchLineEdit->setPlaceholderText("Enter username or last 4 digits of phone...");
    layout->addWidget(searchLineEdit);//Honorable Work by Ziqi ZHAO, 122090793

    QPushButton *searchButton = new QPushButton("Search", cardDialog);//Honorable Work by Ziqi ZHAO, 122090793
    layout->addWidget(searchButton);

    // 结果显示区域
    QTableWidget *resultTable = new QTableWidget(cardDialog);//Honorable Work by Ziqi ZHAO, 122090793
    resultTable->setColumnCount(3);
    resultTable->setHorizontalHeaderLabels({"Name", "Phone", "Balance"});
    resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//Honorable Work by Ziqi ZHAO, 122090793
    layout->addWidget(resultTable);

    // 充值按钮和注册按钮
    QPushButton *payButton = new QPushButton("Pay the Bill", cardDialog);
    QPushButton *rechargeButton = new QPushButton("Recharge", cardDialog);//Honorable Work by Ziqi ZHAO, 122090793
    QPushButton *registerButton = new QPushButton("Register New Card", cardDialog);
    layout->addWidget(payButton);
    layout->addWidget(rechargeButton);//Honorable Work by Ziqi ZHAO, 122090793
    layout->addWidget(registerButton);
//Honorable Work by Ziqi ZHAO, 122090793

    // 连接付款按钮
    QObject::connect(payButton, &QPushButton::clicked, [=]() {
        if (resultTable->rowCount() == 0) {//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::warning(cardDialog, "Payment Error", "No member selected.");
            return;
        }

        int selectedRow = resultTable->currentRow();//Honorable Work by Ziqi ZHAO, 122090793
        if (selectedRow == -1) {
            QMessageBox::warning(cardDialog, "Payment Error", "Please select a member card to pay the bill.");
            return;
        }

        QString memberName = resultTable->item(selectedRow, 0)->text();
        for (auto &card : memberCardList) {
            if (card.name == memberName) {//Honorable Work by Ziqi ZHAO, 122090793
                card.balance -= total_amount;
                if (card.balance < 0) {
                    card.balance += total_amount;//Honorable Work by Ziqi ZHAO, 122090793
                    QMessageBox::information(cardDialog, "Fail", QString("The balance in %1's card is not enough. Please recharge!").arg(memberName));
                } else {
                    QMessageBox::information(cardDialog, "Success", QString("Payment successful. Remaining balance: $%1").arg(card.balance));
                    cardDialog->accept();
                    updateDatabase();  // 更新数据库//Honorable Work by Ziqi ZHAO, 122090793
                }
                resultTable->setItem(selectedRow, 2, new QTableWidgetItem(QString("$%1").arg(card.balance)));
                break;//Honorable Work by Ziqi ZHAO, 122090793
            }
        }
    });


    // 连接搜索按钮的点击信号
    QObject::connect(searchButton, &QPushButton::clicked, [=]() {
        QString input = searchLineEdit->text();
        if (input.isEmpty()) {//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::warning(cardDialog, "Input Error", "Please enter a valid input for search.");
            return;
        }

        // 从文件重新加载数据
        readMemberCardListFromFile(databaseFile, memberCardList);//Honorable Work by Ziqi ZHAO, 122090793

        // 搜索逻辑：遍历从文件读取的列表
        resultTable->setRowCount(0);  // 清空之前的结果
        int row = 0;
        for (const auto &card : memberCardList) {
            if (card.name.contains(input, Qt::CaseInsensitive) || card.phone.endsWith(input)) {
                resultTable->insertRow(row);//Honorable Work by Ziqi ZHAO, 122090793
                resultTable->setItem(row, 0, new QTableWidgetItem(card.name));
                resultTable->setItem(row, 1, new QTableWidgetItem(card.phone));
                resultTable->setItem(row, 2, new QTableWidgetItem(QString("$%1").arg(card.balance, 0, 'f', 2)));//Honorable Work by Ziqi ZHAO, 122090793
                ++row;
            }
        }

        if (row == 0) {//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::information(cardDialog, "Search Result", "No matching member card found.");
        }
    });


    // 连接充值按钮
    QObject::connect(rechargeButton, &QPushButton::clicked, [=]() {
        if (resultTable->rowCount() == 0) {//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::warning(cardDialog, "Recharge Error", "No member selected.");
            return;
        }

        int selectedRow = resultTable->currentRow();
        if (selectedRow == -1) {//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::warning(cardDialog, "Recharge Error", "Please select a member card to recharge.");
            return;
        }

        QString memberName = resultTable->item(selectedRow, 0)->text();
        bool ok;
        double amount = QInputDialog::getDouble(cardDialog, "Recharge", "Enter amount to recharge:", 0, 0, 10000, 2, &ok);
        if (ok) {//Honorable Work by Ziqi ZHAO, 122090793
            for (auto &card : memberCardList) {
                if (card.name == memberName) {
                    card.balance += amount;//Honorable Work by Ziqi ZHAO, 122090793
                    QMessageBox::information(cardDialog, "Recharge", QString("Recharged $%1 to %2's account.").arg(amount).arg(memberName));
                    resultTable->setItem(selectedRow, 2, new QTableWidgetItem(QString("$%1").arg(card.balance)));
                    updateDatabase();  // 更新数据库
                    break;
                }
            }
        }
    });


    // 连接注册按钮//Honorable Work by Ziqi ZHAO, 122090793
    QObject::connect(registerButton, &QPushButton::clicked, [=]() {
        QString newName = QInputDialog::getText(cardDialog, "Register", "Enter new member name:");
        if (newName.isEmpty()) {//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::warning(cardDialog, "Registration Error", "Name cannot be empty.");
            return;
        }

        QString newPhone = QInputDialog::getText(cardDialog, "Register", "Enter phone number (last 4 digits):");//Honorable Work by Ziqi ZHAO, 122090793
        if (newPhone.isEmpty() || newPhone.length() != 4) {
            QMessageBox::warning(cardDialog, "Registration Error", "Phone number must be exactly 4 digits.");
            return;
        }

        bool ok;//Honorable Work by Ziqi ZHAO, 122090793
        double initialBalance = QInputDialog::getDouble(cardDialog, "Register", "Enter initial balance:", 0, 0, 10000, 2, &ok);
        if (ok) {
            memberCardList.append({newName, newPhone, initialBalance});//Honorable Work by Ziqi ZHAO, 122090793
            QMessageBox::information(cardDialog, "Registration", QString("New member %1 registered successfully.").arg(newName));
            updateDatabase();  // 更新数据库//Honorable Work by Ziqi ZHAO, 122090793
        }
    });


    // 显示对话框
    cardDialog->exec();//Honorable Work by Ziqi ZHAO, 122090793
}



