//Header File for TempOrder Class
//It will be used for values releated to temporary orders 

#pragma once

#include<string>

class TempOrder
{
    public:
        TempOrder();
        
        std::string timeStamp;
        std::string orderType;
        std::string pairName;
        std::string orderStatement;
        std::string exchangeOffer;
        double highPrice;
        double lowPrice;

};
