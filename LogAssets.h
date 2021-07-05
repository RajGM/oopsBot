//Header File for LogAssets Class
//It will be used for storing logs of assets and how they change over time

#pragma once

#include<string>

class LogAssets
{
    public:
        LogAssets();
        
        std::string timeStamp;
        std::string allAssets;

};
