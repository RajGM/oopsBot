//CPP file for Logger
//All function are defined here that will be used to write log to txt files

#include "Logger.h"

Logger::Logger()
{
}

//writeLogAssets_toFile will write contents of logAssetsVector into txt file called "logAssets.txt"
void Logger::writeLogAssets_toFile(std::vector<LogAssets> logAssetsVector)
{
    std::ofstream myfile;

    myfile.open("logAssets.txt");
    myfile << "========TIMESTAMP=========" << "      " << " ========WALLET HOLDING======== " << "\n";
    for (int i = 0; i < logAssetsVector.size(); i++)
    {
        myfile << logAssetsVector[i].timeStamp << "    " << logAssetsVector[i].allAssets << "\n";
    }

    myfile.close();
    std::cout << "COMPLETED writeLogAssets_toFile " << std::endl;
}

//writeSuccessTrade_toFile will write contents of allSuccessTradeVector into txt file called "allSuccessTrades.txt"
void Logger::writeSuccessTrade_toFile(std::vector<SuccessTrade> allSuccessTradeVector)
{
    std::ofstream myfile;

    myfile.open("allSuccessTrades.txt");
    myfile << "========TIMESTAMP=========" << "   " << "TYPE:" << "    " << "===ORDER INFORMATION===" << "    " << "EXCHANGE AVERAGE OFFERING" << "\n";
    for (int i = 0; i < allSuccessTradeVector.size(); i++)
    {
        myfile << allSuccessTradeVector[i].timeStamp << "    " << allSuccessTradeVector[i].orderType << "    " << allSuccessTradeVector[i].orderStatement << "    " << allSuccessTradeVector[i].exchangeOffer << "\n";
    }

    myfile.close();
    std::cout << "COMPLETED writeSuccessTrade_toFile " << std::endl;
}

//writeAskOfferLog_toFile will write contents of allTradeLogVector into txt file called "allTradeLog.txt"
void Logger::writeAskOfferLog_toFile(std::vector<AskOfferLog> allTradeLogVector)
{

    std::ofstream myfile;

    myfile.open("allTradeLog.txt");
    myfile << "========TIMESTAMP=========" << "   " << "TYPE:" << "    " << "===ORDER INFORMATION==="<< "\n";
    for (int i = 0; i < allTradeLogVector.size(); i++)
    {
        myfile << allTradeLogVector[i].timeStamp << "    " << allTradeLogVector[i].orderType << "    " << allTradeLogVector[i].orderStatement << "    "
               << "\n";
    }

    myfile.close();
    std::cout << "COMPLETED writeAskOfferLog_toFile " << std::endl;
}
