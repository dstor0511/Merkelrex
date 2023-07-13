#pragma once

#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <string>
#include <vector>

/** The OrderBook class presents a high-level interface for working with the orders in the order book dataset.
 * It provides functions to retrieve orders based on filters, get information about known products, and perform calculations on the orders.
 */
class OrderBook
{
public:
	/** Construct the OrderBook by reading a CSV data file */
	OrderBook(std::string filename);

	/** Return a vector of all known products in the dataset */
	std::vector<std::string> getKnownProducts();

	/** Return a vector of orders filtered by type, product, and timestamp */
	std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

	/** Get the highest price from a vector of OrderBookEntry objects */
	static double getHighPrice(std::vector<OrderBookEntry> &orders);

	/** Get the lowest price from a vector of OrderBookEntry objects */
	static double getLowPrice(std::vector<OrderBookEntry> &orders);

	/** Get the earliest timestamp in the OrderBook */
	std::string getEarliestTime();

	/** Get the next timestamp after the given timestamp in the OrderBook */
	std::string getNextTime(std::string timestamp);

	/** Insert an OrderBookEntry into the OrderBook */
	void insertOrder(OrderBookEntry &order);

	/** Match asks to bids and generate sales based on the given product and timestamp */
	std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

private:
	std::vector<OrderBookEntry> orders;
};
