#pragma once
#include <string>
#include "OrderBookEntry.h"
#include <vector>
#include <map>

class Candlestick
{
public:
	Candlestick(
		std::string candleTimestamp,
		double candleOpenPrice,
		double candleHighPrice,
		double candleLowPrice,
		double candleClosingPrice);

	std::string candleTimestamp;
	double candleOpenPrice;
	double candleHighPrice;
	double candleLowPrice;
	double candleClosingPrice;
};