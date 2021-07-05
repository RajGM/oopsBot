//header files for Bot
//It includes declaration for functions and variables used throughout the program

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

    //int to check how many periods have been elasped 
    int elaspedPeriod = 0;

    //initialize bot with default values in movingAverageMap
    void botInit();
    
    //trains bot depending with the values passed to make strategy
    void trainBot(std::string pair, double buyPrice, double sellPrice);
    
    //check wheather it is time to buy or sell according to the strategy build using traing bot and saved into movingAverageMap
    std::string checkIsOrder(std::string pair, double buyPrice, double sellPrice);

private:

    //movingAverageMap used to store trading strategy values for each pair
    std::map<std::string, double> movingAverageMap;
};