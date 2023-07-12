#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include "CSVReader.h"
#include "OrderBookEntry.h"

class Wallet {
public:
	Wallet();

	/**Insert currency to the wallet*/
	void insertCurrency(std:: string type, double amount);

	/**Remove currency from the wallet*/
	bool removeCurrency(std:: string type, double amount);

	/**Check if the wallet contains this much currency or more*/
	bool containsCurrency(std:: string type, double amount);

	/**Checks if wallet can cope with this ask or bid*/
	bool canFulfillOrder(OrderBookEntry order);

	/*update the contents of the wallet
	* assumes the order was made by the owner of the wallet
	*/
	void processSale(OrderBookEntry& sale);

	/**Generate a string representation of the wallet, how much amount do you have of each type of currency*/
	std::string toString();


private:
	std::map<std::string, double> currencies;

};
