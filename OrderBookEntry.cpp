#include "OrderBookEntry.h"

/*Define constructor function and define data types of the class as arguments
  of the constructor function, additionally insert the initialization list
  (end of the argument parenthesis) Constructs an OrderBookEntry object with
  the given parameters.
 */
OrderBookEntry::OrderBookEntry(double _price, double _amount,
                               std::string _timestamp, std::string _product,
                               OrderBookType _orderType)
	: price(_price), amount(_amount), timestamp(_timestamp), product(_product),
	  orderType(_orderType) {}

OrderBookType OrderBookEntry::stringToOrderBookType(const std::string &s) {
	if (s == "ask") {
		return OrderBookType::ask;
	}
	if (s == "bid") {
		return OrderBookType::bid;
	}
	return OrderBookType::unknown;
}