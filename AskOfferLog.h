//Header File for AskOfferLog Class
//It will be used for storing logs of all trades passed to exchanges matching engine

#pragma once

#include<string>

class AskOfferLog
{
    public:
        AskOfferLog();
        
        std::string timeStamp;
        std::string orderType;
        std::string orderStatement;

};
