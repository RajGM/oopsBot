//Header File for SuccessTrade Class
//It will be used for storing logs of all Successfull Trade over time 

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
