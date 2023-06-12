#pragma once

#include "OrderBook.h"
#include "OrderBookEntry.h"
#include <vector>

/** The MerkelMain class represents the application itself, and it deals with
 * user input and menu printing. */
class MerkelMain {
public:
	MerkelMain();

	/*This function will initiatize the constructor function */
	void init();

private:
	/*This function will display all the menu options*/
	void printMenu();

	/*This function will handle the help menu*/
	void printHelp();

	/*This function will handle the market stats*/
	void printMarketStats();

	/*This function will handle the offers*/
	void enterOffer();

	/*This function will handle the bids*/
	void enterBid();

	/*This function will handle the wallet*/
	void printWallet();

	/*This function will handle the time frame*/
	void gotoNextTimeframe();

	/*This function will receive and return the user input in response to the menu
	 * option selected*/
	int getUserOption();

	/*This function will handle userOption and execute the desired functionality*/
	void processUserOption(int userOption);

	std::string currentTime;

	OrderBook orderBook{"20200317.csv"};
};