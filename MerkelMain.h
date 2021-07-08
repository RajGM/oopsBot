#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "Bot.h"
#include "LogAssets.h"
#include "AskOfferLog.h"
#include "SuccessTrade.h"
#include "Logger.h"

class MerkelMain
{
public:
    MerkelMain();
    /** Call this to start the sim */
    void init();

private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    double enterAsk(std::string inputUser);
    double enterBid(std::string inputUser);
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);

    //function to start the bot
    void startBot();

    //string for storing currentTime
    std::string currentTime;

    //LogAssets Class Object to use funtionality of class for storing information about assets log
    LogAssets logAssetObject;

    //AskOfferLog Class Object to use funtionality of class for storing information about offers passed to exchange 
    AskOfferLog askOfferObject;

    //SuccessTrade Class Object to use funtionality of class for storing information about successful offers 
    SuccessTrade successTradeObject;

    //Vector with elements of type LogAssets to save all assests change over time
    std::vector<LogAssets> logAssetsVector;

    //Vector with elements of type AskOfferLog to save all information about all trades passed to exchange for matching over time
    std::vector<AskOfferLog> allTradeLogVector;

    //Vector with elements of type SuccessTrade to save all information about all successfull trades over time
    std::vector<SuccessTrade> allSuccessTradeVector;

    //Logger Class used to write logs to txt file
    Logger loggerObject;

    //Functions to call suitable methods to add data to respected vecotrs  
    void writeLogAssetsFunction();
    void writesuccessTradeFunction(std::string currentTime, std::string orderType, std::string orderStatement, std::string exchangeOffer);
    void writeallTradeLogFunction(std::string currentTime, std::string orderType, std::string orderStatement);

    //OrderBook orderBook{"20200317.csv"};
    OrderBook orderBook{"20200601.csv"};
    Wallet wallet;

    int totalTimeStamp;
};
