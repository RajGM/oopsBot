#pragma once

#include<string>

class SuccessTrade
{
    public:
        SuccessTrade();
        
        std::string timeStamp;
        std::string orderType;
        std::string orderStatement;
        std::string exchangeOffer;

};
