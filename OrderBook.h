//Headerfile for OrderBook.h
//Starter Code Files
//No need to change anythign here

#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
    /** construct, reading a csv data file */
        OrderBook(std::string filename);
    /** return vector of all know products in the dataset*/
        std::vector<std::string> getKnownProducts(std::string currentTime);
    /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, 
                                              std::string product, 
                                              std::string timestamp);

        /** returns the earliest time in the orderbook*/
        std::string getEarliestTime();
        /** returns the next time after the 
         * sent time in the orderbook  
         * If there is no next timestamp, wraps around to the start
         * */
        std::string getNextTime(std::string timestamp);

        void insertOrder(OrderBookEntry& order);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

        //used to return live orders of current time from Merklerex exchange  
        std::vector<OrderBookEntry> getLiveOrder(std::string currentTime);

        //used to get count of total entries of timestamp 
        int returnOrderBookSize();
        
        //remove orders from orderBook
        void removeOrder(OrderBookEntry& order);
    private:
        //std::vector<OrderBookEntry> orders;
        std::map<std::string, std::vector<OrderBookEntry> > ordersMap;

};
