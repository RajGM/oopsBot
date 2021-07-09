#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <chrono>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Bot.h"

#include <typeinfo>
#include <string>

#include <stdlib.h>

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    totalTimeStamp = orderBook.returnOrderBookSize();
    wallet.insertCurrency("ETH", 10);
    wallet.insertCurrency("BTC", 10);
    wallet.insertCurrency("DOGE", 1000);
    wallet.insertCurrency("USDT", 1000);

    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue
    std::cout << "6: Continue " << std::endl;
    //
    std::cout << "7: Start the bot " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{

    for (std::string const &p : orderBook.getKnownProducts(currentTime))
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;

        std::cout << "Product: " << p << std::endl;
        entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        std::cout << "Bids seen: " << entries.size() << std::endl;
        std::cout << "Max Bid: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min Bid: " << OrderBook::getLowPrice(entries) << std::endl;
    }
}

double MerkelMain::enterAsk(std::string inputUser)
{
    // std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;

    //if human input
    if (inputUser == "human")
    {
        std::getline(std::cin, input);
    }
    else
    {
        input = inputUser;
    }

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
        return -1.0;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);
            obe.username = "simuser";
            double walletFullFillState = wallet.canFulfillOrder(obe);
            if (walletFullFillState)
            {
                //   std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
                return walletFullFillState;
            }
            else
            {
                //  std::cout << "Wallet has insufficient funds . " << std::endl;
                return 0.0;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
            return -1.0;
        }
    }
}

double MerkelMain::enterBid(std::string inputUser)
{
    //std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;

    if (inputUser == "human")
    {
        std::getline(std::cin, input);
    }
    else
    {
        input = inputUser;
    }

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
        return -1.0;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid);
            obe.username = "simuser";
            double walletFullFillState = wallet.canFulfillOrder(obe);
            if (walletFullFillState)
            {
                //  std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
                return walletFullFillState;
            }
            else
            {
                //std::cout << "Wallet has insufficient funds . " << std::endl;
                return 0.0;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
            return -1.0;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    //  std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts(currentTime))
    {
        // std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        //  std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            //  std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }

    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-7" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::startBot()
{
    Bot bot;
    bot.botInit();
    int trainingPeriod = 10;
    //bot training for the first 6 time frames
    for (int i = 0; i < trainingPeriod; i++)
    {
        for (std::string const &p : orderBook.getKnownProducts(currentTime))
        {

            // std::cout << "Product: " << p << std::endl;
            std::string pairName = p;

            std::vector<OrderBookEntry> entries1 = orderBook.getOrders(OrderBookType::ask,
                                                                       p, currentTime);
            std::vector<OrderBookEntry> entries2 = orderBook.getOrders(OrderBookType::bid, p, currentTime);

            bot.trainBot(pairName, OrderBook::getLowPrice(entries1), OrderBook::getHighPrice(entries2));
        }
        bot.elaspedPeriod += 1;
        gotoNextTimeframe();
    }

    //bot trading for the rest of the time frames
    for (int i = trainingPeriod; i < totalTimeStamp; i++)
    {
        //tempOrders vector to hold info about temporary orders
        TempOrder tempOrderObject;
        std::vector<TempOrder> temporderVector;
        for (std::string const &p : orderBook.getKnownProducts(currentTime))
        {

            std::string pairName = p;

            std::vector<OrderBookEntry> entries1 = orderBook.getOrders(OrderBookType::ask,
                                                                       p, currentTime);
            std::vector<OrderBookEntry> entries2 = orderBook.getOrders(OrderBookType::bid, p, currentTime);

            std::string botOrder = bot.checkIsOrder(pairName, OrderBook::getLowPrice(entries1), OrderBook::getHighPrice(entries2));

            //if bot predicts to buy
            if (botOrder == "buy")
            {
                auto first_token = p.substr(0, p.find('/'));

                if (wallet.currenciesMap.find(first_token) != wallet.currenciesMap.end())
                {

                    std::string orderString = p + "," + std::to_string(OrderBook::getHighPrice(entries1)) + "," + std::to_string(wallet.currencyAmount(first_token) / 1000);
                    double bidState = enterBid(orderString);

                    if (bidState == -1.0)
                    {
                        //   bad input
                    }
                    else if (bidState)
                    {
                        //set flag here
                        //push to temporders
                        
                        std::string exchangeAverage = first_token + ":" + std::to_string(bidState);

                        tempOrderObject.timeStamp = currentTime;
                        tempOrderObject.orderType = "BID";
                        tempOrderObject.orderStatement = orderString;
                        tempOrderObject.exchangeOffer = exchangeAverage;
                        tempOrderObject.pairName = pairName;
                        tempOrderObject.highPrice = OrderBook::getHighPrice(entries1);
                        tempOrderObject.lowPrice = OrderBook::getLowPrice(entries1);
                        temporderVector.push_back(tempOrderObject);

                    }
                    else
                    {
                        writeallTradeLogFunction(currentTime, "BID", orderString);
                    }
                }
            }
            else if (botOrder == "sell")
            {
                //if bot predicts to sell

                //auto second_token = p.substr(p.find('/')+1,p.length());
                //std::cout<<"SECOND TOKEN TEST:"<<second_token<<std::endl;
                //second currency

                auto first_token = p.substr(0, p.find('/'));

                if (wallet.currenciesMap.find(first_token) != wallet.currenciesMap.end())
                {

                    std::string orderString = p + "," + std::to_string(OrderBook::getLowPrice(entries2)) + "," + std::to_string(wallet.currencyAmount(first_token) / 1000);
                    double askState = enterAsk(orderString);

                    if (askState == -1.0)
                    {
                        //bad input
                    }
                    else if (askState)
                    {
                        //push to temp orders

                        std::string exchangeAverage = first_token + ":" + std::to_string(askState);

                        tempOrderObject.timeStamp = currentTime;
                        tempOrderObject.orderType = "ASK";
                        tempOrderObject.orderStatement = orderString;
                        tempOrderObject.exchangeOffer = exchangeAverage;
                        tempOrderObject.pairName = pairName;
                        tempOrderObject.highPrice = OrderBook::getHighPrice(entries1);
                        tempOrderObject.lowPrice = OrderBook::getLowPrice(entries1);
                        temporderVector.push_back(tempOrderObject);

                    }
                    else
                    {
                        writeallTradeLogFunction(currentTime, "ASK", orderString);
                    }
                }
            }
        }

        writeLogAssetsFunction();

        //revoke order
        revokeOrder(temporderVector);
        
        //to here

        bot.elaspedPeriod += 1;
        gotoNextTimeframe();
    }

    //writing all to file

    loggerObject.writeLogAssets_toFile(logAssetsVector);
    loggerObject.writeSuccessTrade_toFile(allSuccessTradeVector);
    loggerObject.writeAskOfferLog_toFile(allTradeLogVector);
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption <= 0 || userOption >= 8) // bad input
    {
        std::cout << "Invalid choice. Choose 1-7" << std::endl;
    }
    else if (userOption == 1)
    {
        printHelp();
    }
    else if (userOption == 2)
    {
        printMarketStats();
    }
    else if (userOption == 3)
    {
        enterAsk("human");
    }
    else if (userOption == 4)
    {
        enterBid("human");
    }
    else if (userOption == 5)
    {
        printWallet();
    }
    else if (userOption == 6)
    {
        gotoNextTimeframe();
    }
    else if (userOption == 7)
    {
        //start the bot traing and then trading
        auto start = std::chrono::high_resolution_clock::now();
        startBot();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Duration in microSeconds:" << duration.count() << std::endl;
    }
}

//function definition for writeLogAssetsFunction
//adds data to logAssetsVector
void MerkelMain::writeLogAssetsFunction()
{

    logAssetObject.timeStamp = "";
    logAssetObject.allAssets = "";

    logAssetObject.timeStamp = currentTime;
    for (const auto &myPair : wallet.currenciesMap)
    {
        std::string tempAssets = myPair.first + ":" + std::to_string(wallet.currencyAmount(myPair.first));
        logAssetObject.allAssets += "  " + tempAssets;
    }

    if (logAssetsVector.size() != 0)
    {
        //check if prev is equal
        if (logAssetsVector[logAssetsVector.size() - 1].timeStamp == logAssetObject.timeStamp && logAssetsVector[logAssetsVector.size() - 1].allAssets == logAssetObject.allAssets)
        {
            //do not push
        }
        else
        {
            logAssetsVector.push_back(logAssetObject);
        }
    }
    else
    {
        logAssetsVector.push_back(logAssetObject);
    }
}

//function definition for writesuccessTradeFunction
//adds data to allSuccessTradeVector
void MerkelMain::writesuccessTradeFunction(std::string currentTime, std::string orderType, std::string orderStatement, std::string exchangeOffer)
{

    successTradeObject.timeStamp = "";
    successTradeObject.orderType = "";
    successTradeObject.orderStatement = "";
    successTradeObject.exchangeOffer = "";

    successTradeObject.timeStamp = currentTime;
    successTradeObject.orderType = orderType;
    successTradeObject.orderStatement = orderStatement;
    successTradeObject.exchangeOffer = exchangeOffer;

    if (allSuccessTradeVector.size() != 0)
    {

        if (allSuccessTradeVector[allSuccessTradeVector.size() - 1].timeStamp == successTradeObject.timeStamp && allSuccessTradeVector[allSuccessTradeVector.size() - 1].orderType == successTradeObject.orderType && allSuccessTradeVector[allSuccessTradeVector.size() - 1].orderStatement == successTradeObject.orderStatement && allSuccessTradeVector[allSuccessTradeVector.size() - 1].exchangeOffer == successTradeObject.exchangeOffer)
        {
            //do not push
        }
        else
        {
            allSuccessTradeVector.push_back(successTradeObject);
        }
    }
    else
    {
        allSuccessTradeVector.push_back(successTradeObject);
    }
}

//function definition for writeallTradeLogFunction
//adds data to allTradeLogVector
void MerkelMain::writeallTradeLogFunction(std::string currentTime, std::string orderType, std::string orderStatement)
{

    askOfferObject.timeStamp = "";
    askOfferObject.orderType = "";
    askOfferObject.orderStatement = "";

    askOfferObject.timeStamp = currentTime;
    askOfferObject.orderType = orderType;
    askOfferObject.orderStatement = orderStatement;

    //allTradeLogVector
    if (allTradeLogVector.size() != 0)
    {

        if (allTradeLogVector[allTradeLogVector.size() - 1].timeStamp == askOfferObject.timeStamp && allTradeLogVector[allTradeLogVector.size() - 1].orderType == askOfferObject.orderType && allTradeLogVector[allTradeLogVector.size() - 1].orderStatement == askOfferObject.orderStatement)
        {
            //do not push
        }
        else
        {
            allTradeLogVector.push_back(askOfferObject);
        }
    }
    else
    {
        allTradeLogVector.push_back(askOfferObject);
    }
}

void MerkelMain::revokeOrder(std::vector<TempOrder> temporderVector){
    for (int i = 0; i < temporderVector.size(); i++)
        {
        
            //withdrawing selling and buying is been randomized so that we be on safer side in terms of trading
            int randomNumber = rand() % 10 + 1;

            if (randomNumber % 2 == 0 && randomNumber % 3 == 0)
            {
                writeallTradeLogFunction(currentTime, temporderVector[i].orderType, temporderVector[i].orderStatement);
                std::vector<std::string> tokensRem = CSVReader::tokenise(temporderVector[i].orderStatement, ',');

                OrderBookEntry obeRemove = CSVReader::stringsToOBE(
                    tokensRem[1],
                    tokensRem[2],
                    currentTime,
                    tokensRem[0],
                    OrderBookType::bid);
                obeRemove.username = "simuser";

                orderBook.removeOrder(obeRemove);
            }
            else
            {
                writesuccessTradeFunction(currentTime, temporderVector[i].orderType, temporderVector[i].orderStatement, temporderVector[i].exchangeOffer);
                writeallTradeLogFunction(currentTime, temporderVector[i].orderType, temporderVector[i].orderStatement);
            }
        }
}