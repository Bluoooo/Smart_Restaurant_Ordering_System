#ifndef CARD_H
#define CARD_H
#include <QList>
#include <QString>

// 定义会员卡信息结构
struct MemberCard {//Honorable Work by Ziqi ZHAO, 122090793
    QString name;
    QString phone;
    double balance;
};

// 从文件读取会员卡列表
void readMemberCardListFromFile(const QString &fileName, QList<MemberCard> &list);//Honorable Work by Ziqi ZHAO, 122090793

// 将会员卡列表写入文件
void writeMemberCardListToFile(const QString &fileName, const QList<MemberCard> &list);//Honorable Work by Ziqi ZHAO, 122090793

// 在程序启动时加载数据库
void initializeDatabase();//Honorable Work by Ziqi ZHAO, 122090793

// 在程序操作后保存数据库
void updateDatabase();//Honorable Work by Ziqi ZHAO, 122090793

// 显示会员卡对话框
void showCardDialog(double total_amount);//Honorable Work by Ziqi ZHAO, 122090793

#endif // CARD_H
