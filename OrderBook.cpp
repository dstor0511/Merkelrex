#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>

// Construct the OrderBook by reading a CSV data file
OrderBook::OrderBook(std::string filename) {
	orders = CSVReader::readCSV(filename);
}

// Return a vector of all known products in the dataset
std::vector<std::string> OrderBook::getKnownProducts() {
	std::vector<std::string> products;
	std::map<std::string, bool> prodMap;

	// Iterate through each OrderBookEntry and add unique products to the map
	for (OrderBookEntry& e : orders) {
		prodMap[e.product] = true;
	}

	// Convert the map keys to a vector of products
	for (auto const& e : prodMap) {
		products.push_back(e.first);
	}

	return products;
}

// Return a vector of Orders according to the specified filters (type, product, timestamp)
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp) {
	std::vector<OrderBookEntry> orders_sub;

	// Iterate through each OrderBookEntry and add matching orders to the vector
	for (OrderBookEntry& e : orders) {
		if (e.orderType == type && e.product == product && e.timestamp == timestamp) {
			orders_sub.push_back(e);
		}
	}

	return orders_sub;
}

// Get the highest price from a vector of OrderBookEntry objects
double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
	double max = orders[0].price;

	// Iterate through each OrderBookEntry and update the maximum price if found
	for (OrderBookEntry& e : orders) {
		if (e.price > max) {
			max = e.price;
		}
	}

	return max;
}

// Get the lowest price from a vector of OrderBookEntry objects
double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) {
	double min = orders[0].price;

	// Iterate through each OrderBookEntry and update the minimum price if found
	for (OrderBookEntry& e : orders) {
		if (e.price < min) {
			min = e.price;
		}
	}

	return min;
}

// Get the earliest timestamp in the OrderBook
std::string OrderBook::getEarliestTime() {
	return orders[0].timestamp;
}

// Get the next timestamp after the given timestamp in the OrderBook
std::string OrderBook::getNextTime(std::string timestamp) {
	std::string next_timestamp = "";

	// Iterate through each OrderBookEntry and find the next timestamp
	for (OrderBookEntry& e : orders) {
		if (e.timestamp > timestamp) {
			next_timestamp = e.timestamp;
			break;
		}
	}

	// If no next timestamp is found, wrap around to the start by using the earliest timestamp
	if (next_timestamp == "") {
		next_timestamp = orders[0].timestamp;
	}

	return next_timestamp;
}

// Insert an OrderBookEntry into the OrderBook
void OrderBook::insertOrder(OrderBookEntry& order) {
	orders.push_back(order);
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimeStamp);
}

// Match asks to bids and generate sales based on the given product and timestamp
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
	std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
	std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
	std::vector<OrderBookEntry> sales;

	// Sort asks in ascending order of price
	std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

	// Sort bids in descending order of price
	std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

	// Iterate through asks and bids to match and generate sales
	for (OrderBookEntry& ask : asks) {
		for (OrderBookEntry& bid : bids) {
			if (bid.price >= ask.price) {
				OrderBookEntry sale{ ask.price, 0, timestamp, product, OrderBookType::asksale };

				// Adjust sale parameters based on bid and ask types
				if (bid.username == "simuser") {
					sale.username = "simuser";
					sale.orderType = OrderBookType::bidsale;
				}
				if (ask.username == "simuser") {
					sale.username = "simuser";
					sale.orderType = OrderBookType::asksale;
				}

				// Match bids and asks based on their amounts
				if (bid.amount == ask.amount) {
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = 0;
					break;
				}
				if (bid.amount > ask.amount) {
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount -= ask.amount;
					break;
				}
				if (bid.amount < ask.amount && bid.amount > 0) {
					sale.amount = bid.amount;
					sales.push_back(sale);
					ask.amount -= bid.amount;
					bid.amount = 0;
					continue;
				}
			}
		}
	}

	return sales;
}
