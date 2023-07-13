#include "OrderBookEntry.h"

/* Constructor: Constructs an OrderBookEntry object with the given parameters. */
OrderBookEntry::OrderBookEntry(double _price,
							   double _amount,
							   std::string _timestamp,
							   std::string _product,
							   OrderBookType _orderType,
							   std::string _username)
	: price(_price),
	  amount(_amount),
	  timestamp(_timestamp),
	  product(_product),
	  orderType(_orderType),
	  username(_username)
{
}

/* Converts a string to an OrderBookType enum value. */
OrderBookType OrderBookEntry::stringToOrderBookType(const std::string &s)
{
	if (s == "ask")
	{
		return OrderBookType::ask;
	}
	if (s == "bid")
	{
		return OrderBookType::bid;
	}
	return OrderBookType::unknown;
}
