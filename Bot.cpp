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

void Bot::botInit()
{
    movingAverageMap.insert(std::pair<std::string,double>("BTC/USDT",0));
    movingAverageMap.insert(std::pair<std::string,double>("DOGE/BTC",0));
    movingAverageMap.insert(std::pair<std::string,double>("DOGE/USDT",0));
    movingAverageMap.insert(std::pair<std::string,double>("ETH/BTC",0));
    movingAverageMap.insert(std::pair<std::string,double>("ETH/USDT",0));
}


void Bot::trainBot(std::string pair, double buyPrice,double sellPrice){

    double currentTimePeriodAverage = (buyPrice + sellPrice)/2;
    int timePeriod = elaspedPeriod + 1;
    double currentAverage = ( movingAverageMap.find(pair)->second + currentTimePeriodAverage )/timePeriod;
    movingAverageMap.at(pair) = currentAverage; 

}

std::string Bot::checkIsOrder(std::string pair, double buyPrice,double sellPrice){

    double strategyMA =  movingAverageMap.find(pair)->second;
    double currentTimePeriodAverage = (buyPrice + sellPrice)/2;
    int timePeriod = elaspedPeriod + 1;
    double currentAverage = ( movingAverageMap.find(pair)->second + currentTimePeriodAverage )/timePeriod;

    movingAverageMap.at(pair) = currentAverage; 

    if(strategyMA >= currentAverage){
        return "buy";
    }else{
        return "sell";
    }

    return "noorder";

}