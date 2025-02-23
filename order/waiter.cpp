#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


//预先设置好的服务员绩效文件名
string filename="D:\\Users\\HUAWEI\\CLionProjects\\untitled\\CSC3002\\waiter";

//读取文件中已有的服务员评分
bool FormerRates(const string& filename, map<string, vector<int>>& Waiter_Rate){
    string Waiter_Number;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open" << filename << endl;
        return false;
    }
    string line;
    while (getline(file,line)){
        stringstream ss(line);
        string Rate;
        vector<float> Rates;
        getline(ss,Waiter_Number,',');

        while(getline(ss,Rate,',')){
            try {
                if (!Rate.empty()) {
                    Rates.push_back(stof(Rate));
                } else {
                    cout << "Empty rate found for " << Waiter_Number << endl;
                }
            } catch (const invalid_argument& e) {
                cout << "Invalid rate value: " << Rate << endl;
            } catch (const out_of_range& e) {
                cout << "Rate value out of range: " << Rate << endl;
            }
        }
        Waiter_Rate[Waiter_Number].insert(Waiter_Rate[Waiter_Number].end(), Rates.begin(), Rates.end());
    }
    file.close();
    return true;
}



//写入新的评分
void AddWaiter_Rate(const string& Waiter_Number, int Rate) {
    // 文件路径
    string filename = "D:\\Users\\HUAWEI\\CLionProjects\\untitled\\CSC3002\\waiter";

    // 读取文件内容
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Failed to open file!" << endl;
        return;
    }

    // 存储文件中的每一行
    vector<string> lines;
    string line;
    while (getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();  // 关闭读取文件

    // 打开文件用于写入修改内容
    ofstream outfile(filename, ios::trunc);
    if (!outfile.is_open()) {
        cerr << "Failed to open file for writing!" << endl;
        return;
    }

    // 遍历每一行，找到 Waiter_Number 并添加评分
    for (auto& line : lines) {
        stringstream ss(line);
        string waiterNumber;
        getline(ss, waiterNumber, ',');  // 读取逗号前的 Waiter_Number

        if (waiterNumber == Waiter_Number) {
            // 如果 Waiter_Number 匹配，在逗号后添加评分
            line += "," + to_string(Rate);
        }

        // 将修改后的行写回文件
        outfile << line << endl;
    }

    outfile.close();  // 关闭写入文件
}



//计算平均好评率
double Calculate_Average(const vector<int>& Rates){
    if (Rates.empty()) return 0.0;
    int sum = 0;
    for (int Rate : Rates) {
        sum += Rate;
    }
    return static_cast<double>(sum) / Rates.size();
}


//获取平均好评率
double Get_Average_Rate(const map<string, vector<int>>& Waiter_Rate, const string& Waiter_Number){
    auto it = Waiter_Rate.find(Waiter_Number);
    if (it != Waiter_Rate.end()) {
        return Calculate_Average(it->second);
    } else {
        cout << "Does not find Waiter Number " << Waiter_Number << endl;
        return -1.0; //没找到时的返回值，便于分辨
    }
}


//根据好评率分为五个提成区间
char getGradeByAverage(double average) {
    if (average > 8 && average <= 10) return 'A';
    if (average > 6 && average <= 8) return 'B';
    if (average > 4 && average <= 6) return 'C';
    if (average > 2 && average <= 4) return 'D';
    if (average >= 0 && average <= 2) return 'E';
    return 'F'; // 好评率为负
}


//打印所有人的平均和等第（与后者选用一个即可）
void printAllWaiterGrades(const map<string, vector<int>>& Waiter_Rate) {
    cout << endl << "Your average Rank and Grade" << endl;
    for (const auto& [Waiter_Number, Rates] : Waiter_Rate) {
        double average = Calculate_Average(Rates);
        char grade = getGradeByAverage(average);
        cout << "Your id:" << Waiter_Number << " Average Rate is:" << fixed << setprecision(2) << average
             << " Grade " << grade << endl;
    }
}


//打印特定人的平均和等第（与前者选用一个即可）
vector<string> queryWaiterGrade(const map<string, vector<int>>& Waiter_Rate, const string& Waiter_Number, float totalSum) {
    vector<string> result;

    auto it = Waiter_Rate.find(Waiter_Number);
    if (it == Waiter_Rate.end()) {
        result.push_back("Waiter Number " + Waiter_Number + "'s information can not be found");
        return result;
    }

    const vector<int>& Rates = it->second;
    double average = Calculate_Average(Rates);
    char grade = getGradeByAverage(average);
    float commission = 0;

    switch(grade) {
    case 'A':
        commission += 0.4;
        break;
    case 'B':
        commission += 0.3;
        break;
    case 'C':
        commission += 0.2;
        break;
    case 'D':
        commission += 0.1;
        break;
    case 'F':
        commission += 0.0;
        break;
    default:
        result.push_back("Invalid grade calculation.");
        return result;
    }

    float Salary = totalSum * commission + 3000;

    // 将每个信息段添加到 vector 中
    result.push_back( Waiter_Number);
    result.push_back(to_string(average));
    result.push_back(string(1, grade));
    result.push_back(to_string(Salary));

    return result;
}

int countCommasInLine(const string& line) {
    // 计算一行中逗号的个数
    int count = 0;
    for (char ch : line) {
        if (ch == ',') {
            count++;
        }
    }
    return count;
}

int countCommasInFile(const string& filename,std::string waiterid) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return 0;
    }

    string line;
    while (getline(file, line)) {
        // 检查是否是以 "Waiter_Number" 开头
        if (line.find(waiterid) == 0) {  // 0 表示从行首开始检查
            int commaCount = countCommasInLine(line);
           return commaCount;
        }
    }

    file.close();
}

//主函数，现选用特定人查询，如需可改为全体查询和打印
vector<string> waitor_example(const string& Waiter_Number) {
    map<string, vector<int>> Waiter_Rate;
    // string filename = "Waiter.txt"; // 假设加载的数据源文件
    if (FormerRates(filename, Waiter_Rate)) {
        map<string, vector<int>>::iterator it = Waiter_Rate.begin();
        while (it != Waiter_Rate.end()) {
            ++it;
        }
    } else {
        return {"Fail to load waiter information"};
    }

    // 定义 totalSum，临时参数，之后改为其他函数返回值 OrderOperator.getTotalCost()
    int order_num=countCommasInFile(filename, Waiter_Number);
    float totalSum = 150*order_num;

    // 查询并返回该服务员的平均成绩及等第
    return queryWaiterGrade(Waiter_Rate, Waiter_Number, totalSum);
}
