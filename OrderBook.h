#pragma once

#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <string>
#include <vector>

/** The OrderBook class presents a high level interface on all the orders in the
 * order book data set, including query functions to find out which products are
 * in the data set, and to retrieve a subset of the orders using filters.*/
class OrderBook {
public:
	/** Construct, reading a csv data file */
	OrderBook(std::string filename);

	/** return vector of all known products in the dataset */
	std::vector<std::string> getKnownProducts();

	/** return vector of al Orders according to the sent filters*/
	std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product,
	                                      std::string timestamp);

	/**Returns the earliest time in the orderbook*/
	std::string getEarliestTime();

	/**Returns the next time after the sent time in the orderbook. If there is no next time stamp, wraps around to the start */
	std::string getNextTime(std::string timestamp);

	void insertOrder(OrderBookEntry& order);

	/**This function is going to be sent a set of orders and its job is to find
	 * the highest price in those orders. */
	static double getHighPrice(std::vector<OrderBookEntry> &orders);
	static double getLowPrice(std::vector<OrderBookEntry> &orders);

private:
	std::vector<OrderBookEntry> orders;
};