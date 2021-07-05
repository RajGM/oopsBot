#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include <map>

class Bot
{
    public:

        Bot();
        int elaspedPeriod = 0;
        void botInit();
        void trainBot(std::string pair, double buyPrice,double sellPrice);
        std::string checkIsOrder(std::string pair, double buyPrice,double sellPrice);
        

    private: 
     std::map<std::string,int> movingAverageMap;


};