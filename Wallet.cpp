#include "Wallet.h"

Wallet::Wallet() {
	// Default constructor
}

/** Inserts currency into the wallet.
 * @param type The type of currency to insert.
 * @param amount The amount of currency to insert.
 */
void Wallet::insertCurrency(std::string type, double amount) {
	double balance;

	if (amount < 0) {
		throw std::exception{};
	}

	// Check if the currency already exists in the wallet
	if (currencies.count(type) == 0) {
		balance = 0;
	} else {
		balance = currencies[type];
	}

	// Update the balance by adding the amount
	balance += amount;

	// Store the updated balance in the wallet
	currencies[type] = balance;
}

/** Removes currency from the wallet.
 * @param type The type of currency to remove.
 * @param amount The amount of currency to remove.
 * @return True if the currency was successfully removed, false otherwise.
 */
bool Wallet::removeCurrency(std::string type, double amount) {
	if (amount < 0) {
		return false;
	}

	// Check if the currency exists in the wallet
	if (currencies.count(type) == 0) {
		return false;
	} else {
		// Check if the wallet contains enough currency to remove
		if (containsCurrency(type, amount)) {
			currencies[type] -= amount;
			return true;
		} else {
			return false; // Not enough currency in the wallet
		}
	}
}

/** Checks if the wallet contains a specific amount of currency or more.
 * @param type The type of currency to check.
 * @param amount The amount of currency to check.
 * @return True if the wallet contains the specified amount of currency or more, false otherwise.
 */
bool Wallet::containsCurrency(std::string type, double amount) {
	if (currencies.count(type) == 0) {
		return false; // Currency does not exist in the wallet
	} else {
		return currencies[type] >= amount; // Check if the balance is greater than or equal to the requested amount
	}
}

/** Checks if the wallet can fulfill an order.
 * @param order The OrderBookEntry representing the order to be fulfilled.
 * @return True if the wallet can fulfill the order, false otherwise.
 */
bool Wallet::canFulfillOrder(OrderBookEntry order) {
	std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');

	// Check if the order is an ask
	if (order.orderType == OrderBookType::ask) {
		double amount = order.amount;
		std::string currency = currs[0];

		// Check if the wallet contains enough currency to fulfill the ask order
		return containsCurrency(currency, amount);
	}

	// Check if the order is a bid
	if (order.orderType == OrderBookType::bid) {
		double amount = order.amount * order.price;
		std::string currency = currs[1];

		// Check if the wallet contains enough currency to fulfill the bid order
		return containsCurrency(currency, amount);
	}

	return false;
}

/** Updates the contents of the wallet after a sale.
 * @param sale The OrderBookEntry representing the sale.
 */
void Wallet::processSale(OrderBookEntry& sale) {
	std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

	// Check if the sale is an ask sale
	if (sale.orderType == OrderBookType::asksale) {
		double outgoingAmount = sale.amount;
		std::string outgoingCurrency = currs[0];

		double incomingAmount = sale.amount * sale.price;
		std::string incomingCurrency = currs[1];

		// Update the wallet balances
		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}

	// Check if the sale is a bid sale
	if (sale.orderType == OrderBookType::bidsale) {
		double incomingAmount = sale.amount;
		std::string incomingCurrency = currs[0];

		double outgoingAmount = sale.amount * sale.price;
		std::string outgoingCurrency = currs[1];

		// Update the wallet balances
		currencies[incomingCurrency] += incomingAmount;
		currencies[outgoingCurrency] -= outgoingAmount;
	}
}

/** Generates a string representation of the wallet, showing the amount of each currency.
 * @return The string representation of the wallet.
 */
std::string Wallet::toString() {
	std::string s;

	// Iterate over each currency in the wallet
	for (std::pair<std::string, double> pair : currencies) {
		std::string currency = pair.first;
		double amount = pair.second;

		// Append the currency and its amount to the string
		s += currency + " : " + std::to_string(amount) + "\n";
	}

	return s;
}
