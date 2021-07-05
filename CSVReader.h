//Headerfile for CSVReader.h
//No need to change anythign here

#pragma once

#include <iostream>
#include "OrderBookEntry.h"
#include <vector>
#include <string>
#include <map>


class CSVReader
{
    public:
     CSVReader();

     static std::vector<OrderBookEntry> readCSV(std::string csvFile);
     static std::vector<std::string> tokenise(std::string csvLine, char separator);
    
     static OrderBookEntry stringsToOBE(std::string price, 
                                        std::string amount, 
                                        std::string timestamp, 
                                        std::string product, 
                                        OrderBookType OrderBookType);

     static std::map<std::string, std::vector<OrderBookEntry> > readCSVMap(std::string csvFile);

    private:
     static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
     
};