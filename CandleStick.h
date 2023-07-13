#pragma once

#include <string>
#include <vector>
#include "OrderBookEntry.h"

class Candlestick
{
public:
	std::string date;
	double open;
	double high;
	double low;
	double close;

	Candlestick(std::string date, double open, double high, double low, double close);

	static std::vector<Candlestick> computeCandlesticks(std::string csvFilename);

private:
	static Candlestick createCandlestick(const std::vector<OrderBookEntry> &entries);

	// static Candlestick createCandlestick(const std::vector<OrderBookEntry>& entries);
};
