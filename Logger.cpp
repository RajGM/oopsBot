#include "Logger.h"

Logger::Logger()
{
}

void Logger::writeLogAssets_toFile(std::vector<LogAssets> logAssetsVector)
{
    std::ofstream myfile;

    myfile.open("logAssets.txt");

    for (int i = 0; i < logAssetsVector.size(); i++)
    {
        myfile << logAssetsVector[i].timeStamp << "    " << logAssetsVector[i].allAssets << "\n";
    }

    myfile.close();
    std::cout << "COMPLETED writeLogAssets_toFile " << std::endl;
}

void Logger::writeSuccessTrade_toFile(std::vector<SuccessTrade> allSuccessTradeVector)
{
    std::ofstream myfile;

    myfile.open("allSuccessTrades.txt");

    for (int i = 0; i < allSuccessTradeVector.size(); i++)
    {
        myfile << allSuccessTradeVector[i].timeStamp << "    " << allSuccessTradeVector[i].orderType << "    " << allSuccessTradeVector[i].orderStatement << "    " << allSuccessTradeVector[i].exchangeOffer << "\n";
    }

    myfile.close();
    std::cout << "COMPLETED writeSuccessTrade_toFile " << std::endl;
}

void Logger::writeAskOfferLog_toFile(std::vector<AskOfferLog> allTradeLogVector)
{

    std::ofstream myfile;

    myfile.open("allTradeLog.txt");
    
    for (int i = 0; i < allTradeLogVector.size(); i++)
    {
        myfile << allTradeLogVector[i].timeStamp << "    " << allTradeLogVector[i].orderType << "    " << allTradeLogVector[i].orderStatement << "    "
               << "\n";
    }

    myfile.close();
    std::cout << "COMPLETED writeAskOfferLog_toFile " << std::endl;
}
