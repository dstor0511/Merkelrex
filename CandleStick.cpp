#include "CandleStick.h"
#include <string>
#include <vector>

Candlestick::Candlestick(
    std::string candleTimestamp,
    double candleOpenPrice,
    double candleHighPrice,
    double candleLowPrice,
    double candleClosingPrice)
    : candleTimestamp(candleTimestamp),
      candleOpenPrice(candleOpenPrice),
      candleHighPrice(candleHighPrice),
      candleLowPrice(candleLowPrice),
      candleClosingPrice(candleClosingPrice)
{
}