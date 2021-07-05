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

    void startBot();

    std::string currentTime;

    LogAssets logAssetObject;
    AskOfferLog askOfferObject;
    SuccessTrade successTradeObject;

    std::vector<LogAssets> logAssetsVector;
    std::vector<AskOfferLog> allTradeLogVector;
    std::vector<SuccessTrade> allSuccessTradeVector;

    Logger loggerObject;

    void writeLogAssetsFunction();
    void writesuccessTradeFunction(std::string currentTime, std::string orderType, std::string orderStatement, std::string exchangeOffer);
    void writeallTradeLogFunction(std::string currentTime, std::string orderType, std::string orderStatement);

    //        OrderBook orderBook{"20200317.csv"};
    OrderBook orderBook{"20200601.csv"};
    Wallet wallet;
};
