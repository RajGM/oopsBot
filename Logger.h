//Headerfile for LoggerClass
//It will be used for writing for writing all types of logs to txt files 
//All functions are declared here 

#pragma once

#include <iostream>

#include<string>
#include<vector>
#include <fstream>

#include "AskOfferLog.h"
#include "SuccessTrade.h"
#include "LogAssets.h"

class Logger
{
    public:
        Logger();
        
        void writeAskOfferLog_toFile( std::vector<AskOfferLog> allTradeLogVector );
        void writeSuccessTrade_toFile( std::vector<SuccessTrade> allSuccessTradeVector );
        void writeLogAssets_toFile( std::vector<LogAssets> logAssetsVector );

};