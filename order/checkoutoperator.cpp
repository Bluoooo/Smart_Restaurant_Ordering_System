#include "checkoutoperator.h"
#include "OrderOperator.h"
#include "card.h"
//#include "membercard.cpp"
#include <algorithm>
#include <random>
#include <windows.h>
#include <iostream>

checkoutOperator::checkoutOperator(
    OrderOperator* orderOperator,
    std::string WeChatPayQRCodeDir,
    std::string AlipayQRCodeDir,
    float saleRate
) : orderOperator(orderOperator),
    WeChatPayQRCodeDir(WeChatPayQRCodeDir),
    AlipayQRCodeDir(AlipayQRCodeDir),
    saleRate(saleRate) {}

std::vector<std::string> checkoutOperator::getFilesInDirectory(const std::string& path) {
    std::vector<std::string> files;
    std::string search_path = path + "\\*";
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(search_path.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                files.push_back(path + "\\" + findData.cFileName);
            }
        } while (FindNextFileA(hFind, &findData));
        FindClose(hFind);
    } else {
        std::cerr << "Failed to open directory: " << path << std::endl;
    }
    return files;
}

std::string checkoutOperator::getRandomWeChatPayQRCode() {
    std::vector<std::string> files = getFilesInDirectory(WeChatPayQRCodeDir);
    if (files.empty()) {
        return "";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, files.size() - 1);
    return files[dis(gen)];
}

std::string checkoutOperator::getRandomAlipayQRCode() {
    std::vector<std::string> files = getFilesInDirectory(AlipayQRCodeDir);
    if (files.empty()) {
        return "";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, files.size() - 1);
    return files[dis(gen)];
}

void checkoutOperator::payByMemberCard() {
    double totalCost = orderOperator->getTotalCost() * saleRate;
    showCardDialog(totalCost);
    orderOperator->clearOrder();
}



