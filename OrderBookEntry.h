#pragma once
#include <string>

/*This is a class that will store the two options of OrderBookType vector*/
enum class OrderBookType { bid, ask, unknown, asksale, bidsale};

/** The OrderBookEntry represents a row in the order book data set (i.e. a
 * single order in the order book). It can be a bid or an ask order.*/
class OrderBookEntry {

public:
	/*Define constructor function and define data types of the class as arguments
	 * of the constructor function, additionally insert the initialization list
	 * (end of the argument parenthesis)*/
	OrderBookEntry(double _price,
	               double _amount,
	               std::string _timestamp,
	               std::string _product,
	               OrderBookType _orderType,
	               std::string username = "dataset");

	static OrderBookType stringToOrderBookType(const std::string &s);

	static bool compareByTimeStamp(OrderBookEntry& e1, OrderBookEntry& e2) {

		return e1.timestamp < e2.timestamp;
	}

	static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2) {

		return e1.price < e2.price;
	}

	static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2) {

		return e1.price > e2.price;
	}

	/*Data members*/
	double price;
	double amount;
	std::string timestamp;
	std::string product;
	OrderBookType orderType;
	std::string username;
};