#include "CandleStick.h"
#include "CSVReader.h"
#include "OrderBook.h"
#include <iostream>
#include <vector>

std::vector<Candlestick> Candlestick::computeCandlesticks(std::string csvFilename)
{
    // Read the CSV file and obtain the order book entries
    CSVReader csvReader;
    std::vector<OrderBookEntry> entries = csvReader.readCSV(csvFilename);

    std::vector<Candlestick> candlesticks; // Vector to store the candlestick data

    const int timeFrame = 476; // Number of lines per time frame

    if (entries.size() > 0)
    {
        int startIndex = 0;
        int endIndex = timeFrame;

        while (endIndex <= entries.size())
        {
            std::vector<OrderBookEntry> timeFrameEntries(entries.begin() + startIndex, entries.begin() + endIndex);

            if (!timeFrameEntries.empty())
            {
                Candlestick candlestick = createCandlestick(timeFrameEntries);
                candlesticks.push_back(candlestick);
            }

            startIndex = endIndex;
            endIndex += timeFrame;
        }
    }

    return candlesticks;
}

Candlestick Candlestick::createCandlestick(const std::vector<OrderBookEntry> &entries)
{
    double open = entries.front().price;
    double high = OrderBook::getHighPrice(entries);
    double low = OrderBook::getLowPrice(entries);
    double close = entries.back().price;

    Candlestick candlestick("", open, high, low, close); // Empty date, as it is not specified in the provided code

    return candlestick;
}
