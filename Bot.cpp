#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "CSVReader.h"
#include <map>
#include "Bot.h"


#include <typeinfo>

Bot::Bot()
{

}


//initializing movingAverageMap with default values 
void Bot::botInit()
{
    movingAverageMap.insert(std::pair<std::string,double>("BTC/USDT",0));
    movingAverageMap.insert(std::pair<std::string,double>("DOGE/BTC",0));
    movingAverageMap.insert(std::pair<std::string,double>("DOGE/USDT",0));
    movingAverageMap.insert(std::pair<std::string,double>("ETH/BTC",0));
    movingAverageMap.insert(std::pair<std::string,double>("ETH/USDT",0));
}

//trains bot depending with the values passed to make strategy
//trains bot using the formula of simple oving average
//The moving average is calculated by adding a stock's prices over a certain period and dividing the sum by the total number of periods.
// For reference purposes https://www.investopedia.com/ask/answers/042815/how-simple-moving-average-calculated.asp
void Bot::trainBot(std::string pair, double buyPrice,double sellPrice){

    double currentTimePeriodAverage = (buyPrice + sellPrice)/2;
    double currentAverage = ( movingAverageMap.find(pair)->second + currentTimePeriodAverage )/2;
    
    if( movingAverageMap.find(pair)->second == 0){
        movingAverageMap.at(pair) = currentTimePeriodAverage; 
    }else{
        movingAverageMap.at(pair) = currentAverage; 
    }

}

//check wheather it is time to buy or sell according to the strategy build using traing bot and saved into movingAverageMap
//It calculates average of currentTime frame bid and ask values and then compares with movingAverageMap
//If movingAverageMap >=  average of currentTime then buy else sell
std::string Bot::checkIsOrder(std::string pair, double buyPrice,double sellPrice){

    double strategyMA =  movingAverageMap.find(pair)->second;
    double currentTimePeriodAverage = (buyPrice + sellPrice)/2;
    double currentAverage = ( strategyMA + currentTimePeriodAverage )/2;

    movingAverageMap.at(pair) = currentAverage; 

    if(strategyMA >= currentAverage){
        return "buy";
    }else{
        return "sell";
    }

    return "noorder";

}