/*
   This file contains the declaration of the MerkelMain class, which represents
   the application itself. It handles user input, menu printing, and the execution
   of various functionalities.
*/

#pragma once

#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "Wallet.h"
#include <vector>

class MerkelMain
{
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
	void enterAsk();

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

	OrderBook orderBook{"20200601.csv"};

	Wallet wallet;
};