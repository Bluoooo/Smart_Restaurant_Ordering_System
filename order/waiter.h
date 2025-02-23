#ifndef WAITER_H
#define WAITER_H

#include <string>
#include <map>
#include <vector>

// 预设的服务员绩效文件名
extern std::string filename;

// 读取文件中已有的服务员评分
bool FormerRates(const std::string& filename, std::map<std::string, std::vector<int>>& Waiter_Rate);

// 写入新的评分
void AddWaiter_Rate( const std::string& Waiter_Number, int Rate);

// 计算平均好评率
double Calculate_Average(const std::vector<int>& Rates);

// 获取某个服务员的平均好评率
double Get_Average_Rate(const std::map<std::string, std::vector<int>>& Waiter_Rate, const std::string& Waiter_Number);

// 根据好评率分为五个提成区间
char getGradeByAverage(double average);

// 打印所有人的平均和等第
void printAllWaiterGrades(const std::map<std::string, std::vector<int>>& Waiter_Rate);

// 打印特定人的平均和等第，并返回结果
std::vector<std::string> queryWaiterGrade(const std::map<std::string, std::vector<int>>& Waiter_Rate, const std::string& Waiter_Number, float totalSum);

// 主函数，查询特定服务员的评分信息
std::vector<std::string> waitor_example(const std::string& Waiter_Number);


#endif // WAITER_H
