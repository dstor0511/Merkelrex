#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include "CSVReader.h"
#include "OrderBookEntry.h"

class Wallet
{
public:
	Wallet();

	/**
	 * Insert currency to the wallet.
	 *
	 * @param type   The type of currency to insert.
	 * @param amount The amount of currency to insert.
	 */
	void insertCurrency(std::string type, double amount);

	/**
	 * Remove currency from the wallet.
	 *
	 * @param type   The type of currency to remove.
	 * @param amount The amount of currency to remove.
	 * @return       True if the removal was successful, false otherwise.
	 */
	bool removeCurrency(std::string type, double amount);

	/**
	 * Check if the wallet contains at least the specified amount of currency.
	 *
	 * @param type   The type of currency to check.
	 * @param amount The minimum amount of currency to check for.
	 * @return       True if the wallet contains the specified amount of currency or more, false otherwise.
	 */
	bool containsCurrency(std::string type, double amount);

	/**
	 * Check if the wallet has sufficient funds to fulfill the given order.
	 *
	 * @param order The order to fulfill.
	 * @return      True if the wallet has sufficient funds, false otherwise.
	 */
	bool canFulfillOrder(OrderBookEntry order);

	/**
	 * Process a sale and update the contents of the wallet.
	 *
	 * @param sale The sale to process.
	 */
	void processSale(OrderBookEntry &sale);

	/**
	 * Generate a string representation of the wallet, showing the amount of each type of currency.
	 *
	 * @return The string representation of the wallet.
	 */
	std::string toString();

private:
	std::map<std::string, double> currencies;
};
