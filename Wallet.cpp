//C++ file for Wallet
//StarterCode file 
//No need to change anything here

#include "Wallet.h"
#include <iostream>
#include "CSVReader.h"

Wallet::Wallet()
{
}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance;
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type) == 0) // not there yet
    {
        balance = 0;
    }
    else
    { // is there
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;

    currenciesMap[type] = true;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0)
    {
        return false;
    }
    if (currencies.count(type) == 0) // not there yet
    {
        //std::cout << "No currency for " << type << std::endl;
        return false;
    }
    else
    {                                       // is there - do  we have enough
        if (containsCurrency(type, amount)) // we have enough
        {
            //std::cout << "Removing " << type << ": " << amount << std::endl;
            currencies[type] -= amount;
            return true;
        }
        else // they have it but not enough.
            return false;
    }
}

double Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0 || currencies[type] < amount) // not there yet
        return 0.0;
    else
        return currencies[type];
}

std::string Wallet::toString()
{
    std::string s;
    for (std::pair<std::string, double> pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

double Wallet::canFulfillOrder(OrderBookEntry order)
{
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    // ask
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0];
        //std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;

        if( containsCurrency(currency, amount) ){
            return amount;
        }else{
            return 0;
        }
        
    }
    // bid
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        //std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        
        if( containsCurrency(currency, amount) ){
            return amount;
        }else{
            return 0;
        }
        
    }

    return 0;
}

void Wallet::processSale(OrderBookEntry &sale)
{
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    // ask
    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    // bid
    if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}
std::ostream &operator<<(std::ostream &os, Wallet &wallet)
{
    os << wallet.toString();
    return os;
}

double Wallet::currencyAmount(std::string type)
{

    if ( currenciesMap.find(type) != currenciesMap.end())
    {
        if( currencies[type]>0.0 ){
            return currencies[type];
        }

    }

    return 0.0;

}