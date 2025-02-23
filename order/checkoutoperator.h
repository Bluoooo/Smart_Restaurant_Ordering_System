#ifndef CHECKOUTOPERATOR_H
#define CHECKOUTOPERATOR_H
#include "OrderOperator.h"
#include <string>
#include <vector>

class checkoutOperator
{
public:
    checkoutOperator(
        OrderOperator* orderOperator,
        // eg: "C:/Users/wutong/OneDrive - CUHK-Shenzhen/university/csc/csc3002/project/QT Creator my function test/WeChatPayQRCode"
        std::string WeChatPayQRCodeDir,
        std::string AlipayQRCodeDir,
        float saleRate // eg: 0.95 for 95% off 95折
    );

    std::string getRandomWeChatPayQRCode();
    std::string getRandomAlipayQRCode();
    std::vector<std::string> getFilesInDirectory(const std::string& path);

    void payByMemberCard();

private:
    OrderOperator* orderOperator;
    std::string WeChatPayQRCodeDir;
    std::string AlipayQRCodeDir;
    float saleRate;
};

#endif // CHECKOUTOPERATOR_H
