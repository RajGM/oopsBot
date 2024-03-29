//C++ file for OrderBook
//StarterCode file
//No need to change anything here

#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
#include <iostream>

/** construct, reading a csv data file */
OrderBook::OrderBook(std::string filename)
{
    ordersMap = CSVReader::readCSVMap(filename);
}

/** return vector of all know products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts(std::string currentTime)
{
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for (OrderBookEntry &e : ordersMap[currentTime])
    {
        prodMap[e.product] = true;
    }

    for (auto const &e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}
/** return vector of Orders according to the sent filters*/

//efficiency fixed
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp)
{

    std::vector<OrderBookEntry> Efficientorders_sub;

    for (auto &x : ordersMap[timestamp])
    {

        if (x.orderType == type && x.product == product && x.timestamp == timestamp)
        {
            Efficientorders_sub.push_back(x);
        }
    }

    return Efficientorders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price > max)
            max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double min = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price < min)
            min = e.price;
    }
    return min;
}

std::string OrderBook::getEarliestTime()
{
    return ordersMap.begin()->first;
}

std::vector<OrderBookEntry> OrderBook::getLiveOrder(std::string currentTime)
{

    std::vector<OrderBookEntry> currentTimeLiveOrders = ordersMap[currentTime];

    return currentTimeLiveOrders;
}

std::string OrderBook::getNextTime(std::string timestamp)
{

    std::map<std::string, std::vector<OrderBookEntry>>::iterator it;
    it = ordersMap.find(timestamp);

    if (it == ordersMap.end())
    {
        it = ordersMap.begin();
        std::cout << "======================THIS IS THE LAST ELEMENT===========================" << std::endl;
    }
    else
    {
        it++;
    }

    return it->first;
}

void OrderBook::insertOrder(OrderBookEntry &order)
{
    std::vector<OrderBookEntry> orderVector = ordersMap[order.timestamp];
    orderVector.push_back(order);
    ordersMap[order.timestamp] = orderVector;
}

 void OrderBook::removeOrder(OrderBookEntry& order){
    std::vector<OrderBookEntry> orderVector = ordersMap[order.timestamp];
    
    for(int i=0;i<orderVector.size();i++){
        if( orderVector[i].timestamp == order.timestamp
        && orderVector[i].orderType == order.orderType 
        && orderVector[i].product == order.product 
        && orderVector[i].amount == order.amount 
        && orderVector[i].username == order.username
        && orderVector[i].price == order.price 
        ){
            orderVector.erase(orderVector.begin()+i);
            break;
        }
    }

    ordersMap[order.timestamp] = orderVector;
 }

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    // asks = orderbook.asks
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                 product,
                                                 timestamp);
    // bids = orderbook.bids
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                 product,
                                                 timestamp);

    // sales = []
    std::vector<OrderBookEntry> sales;

    // I put in a little check to ensure we have bids and asks
    // to process.
    if (asks.size() == 0 || bids.size() == 0)
    {
        std::cout << " OrderBook::matchAsksToBids no bids or asks" << std::endl;
        return sales;
    }

    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    // for ask in asks:

    //commented out for testing purposes
    //std::cout << "max ask " << asks[asks.size()-1].price << std::endl;
    //std::cout << "min ask " << asks[0].price << std::endl;
    //std::cout << "max bid " << bids[0].price << std::endl;
    //std::cout << "min bid " << bids[bids.size()-1].price << std::endl;

    for (OrderBookEntry &ask : asks)
    {
        //     for bid in bids:
        for (OrderBookEntry &bid : bids)
        {
            //         if bid.price >= ask.price # we have a match
            if (bid.price >= ask.price)
            {
                //             sale = new order()
                //             sale.price = ask.price
                OrderBookEntry sale{ask.price, 0, timestamp,
                                    product,
                                    OrderBookType::asksale};

                if (bid.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                }
                if (ask.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }

                //             # now work out how much was sold and
                //             # create new bids and asks covering
                //             # anything that was not sold
                //             if bid.amount == ask.amount: # bid completely clears ask
                if (bid.amount == ask.amount)
                {
                    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
                    //                 # can do no more with this ask
                    //                 # go onto the next ask
                    //                 break
                    break;
                }
                //           if bid.amount > ask.amount:  # ask is completely gone slice the bid
                if (bid.amount > ask.amount)
                {
                    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 # we adjust the bid in place
                    //                 # so it can be used to process the next ask
                    //                 bid.amount = bid.amount - ask.amount
                    bid.amount = bid.amount - ask.amount;
                    //                 # ask is completely gone, so go to next ask
                    //                 break
                    break;
                }

                //             if bid.amount < ask.amount # bid is completely gone, slice the ask
                if (bid.amount < ask.amount &&
                    bid.amount > 0)
                {
                    //                 sale.amount = bid.amount
                    sale.amount = bid.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 # update the ask
                    //                 # and allow further bids to process the remaining amount
                    //                 ask.amount = ask.amount - bid.amount
                    ask.amount = ask.amount - bid.amount;
                    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
                    //                 # some ask remains so go to the next bid
                    //                 continue
                    continue;
                }
            }
        }
    }
    return sales;
}

int OrderBook::returnOrderBookSize()
{
    return ordersMap.size();
}