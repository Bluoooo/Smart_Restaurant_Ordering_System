#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
using namespace std;


const int NUM_TABLES = 25;
const string BASE_PATH = "D:\\HUAWEI\\Desktop\\test_1130\\table_orders";//假设是这个，后续根据具体的更改



//随机生成用餐时间，区间为【20，60】（已测试）
int generateDiningTime() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10, 15);
    return dis(gen);
}




// 创建餐桌信息文件
void initializeTable(int tableNumber) {
    int diningTime = generateDiningTime();
    stringstream fileName;
    fileName << BASE_PATH << "table_time_" << tableNumber << ".txt";
    ofstream tableFile(fileName.str());
    if (tableFile.is_open()) {
        tableFile << "Dining Time: " << diningTime << " minutes" << endl;
        tableFile << "Service details: Waiting for service." << endl;
        tableFile.close();
        cout << "Table " << tableNumber << " initialized with dining time " << diningTime << " minutes." << endl;
    } else {
        cerr << "Failed to create file for table " << tableNumber << endl;
    }
}


// 模拟餐桌用餐过程
void serveTable(int tableNumber) {
    stringstream fileName;
    fileName << BASE_PATH << "table_" << tableNumber << ".txt";


    //需要两个cin，分别是服务员号和所点的菜
    string Waiter_Number, dish;
    //需要两个cin，分别是服务员号和所点的菜

    ofstream tableFile(fileName.str(), ios::app); // 追加模式
    if (tableFile.is_open()) {
        tableFile << "Waiter ID: " << Waiter_Number << endl;
        tableFile << "Dish: " << dish << endl;
        tableFile.close();
    } else {
        cerr << "Failed to open file for table " << tableNumber << endl;
        return;
    }

    // 模拟用餐过程，等待用餐时间（休眠一段时间）
    int diningTime = generateDiningTime();
    Sleep(diningTime);

    // 用餐结束后清空文件
    ofstream tableFileClear(fileName.str(), ios::trunc);
    if (tableFileClear.is_open()) {
        tableFileClear.close();
    } else {
        //正常情况下不会用到，只有发生错误时才会
        cerr << "Failed to clear file for table " << tableNumber << endl;
    }
}


//原main函数
int example(){
    for (int i = 1; i <= NUM_TABLES; ++i) {
        initializeTable(i);
    }
    for (int i = 1; i <= NUM_TABLES; ++i) {
        serveTable(i);
    }

    return 0;
}







