/*
   MerkelMain.cpp

   This file contains the implementation of the MerkelMain class, which represents
   the application itself. It handles user input, menu printing, and the execution
   of various functionalities.
*/

#include "MerkelMain.h"
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>
#include <limits> // Include the <limits> header

MerkelMain::MerkelMain() {
	// Constructor implementation
}

void MerkelMain::init() {
	int input;
	currentTime = orderBook.getEarliestTime();

	wallet.insertCurrency("BTC", 10);

	while (true) {
		printMenu();
		input = getUserOption();
		processUserOption(input);
	}
}

void MerkelMain::printMenu() {
	// Print the menu options
	std::cout << "1: Print help" << std::endl;
	std::cout << "2: Print exchange stats" << std::endl;
	std::cout << "3: Make an offer" << std::endl;
	std::cout << "4: Make a bid" << std::endl;
	std::cout << "5: Print wallet" << std::endl;
	std::cout << "6: Continue" << std::endl;
	std::cout << "============== " << std::endl;
	std::cout << "Current Time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp() {
	// Print the help information
	std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers." << std::endl;
}

void MerkelMain::printMarketStats() {
	// Print the market statistics
	for (std::string const &p : orderBook.getKnownProducts()) {
		std::cout << "Product: " << p << std::endl;
		std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
		std::cout << "Asks for product seen: " << entries.size() << std::endl;
		std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
		std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
	}
}

void MerkelMain::enterAsk() {
	// Handle entering an ask
	std::cout << "Mark and ask - enter the amount: product,price,amount, e.g., ETH/BTC,200,0.5" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

	if (tokens.size() != 3 ) {
		std::cout << "Bad input!" << input << "Please make sure you don't use spaces between the 3 values" << std::endl;
	}
	else {
		try {
			OrderBookEntry obe = CSVReader::stringsToOBE(
			                         tokens[1],
			                         tokens[2],
			                         currentTime,
			                         tokens[0],
			                         OrderBookType::ask
			                     );
			obe.username = "simuser";
			if (wallet.canFulfillOrder(obe)) {
				std::cout << "Wallet looks good." << std::endl;
				orderBook.insertOrder(obe);
			}
			else {
				std::cout << "Insufficient funds." << std::endl;
			}
		}
		catch (const std::exception& e) {
			std::cout << "MerkelMain::enterAsk Bad input" << std::endl;
		}
	}

	std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::enterBid() {
	// Handle entering a bid
	std::cout << "Make a bid - enter the amount: product,price,amount, e.g., ETH/BTC,200,0.5" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

	if (tokens.size() != 3 ) {
		std::cout << "Bad input!" << input << "Please make sure you don't use spaces between the 3 values" << std::endl;
	}
	else {
		try {
			OrderBookEntry obe = CSVReader::stringsToOBE(
			                         tokens[1],
			                         tokens[2],
			                         currentTime,
			                         tokens[0],
			                         OrderBookType::bid
			                     );

			obe.username = "simuser";
			if (wallet.canFulfillOrder(obe)) {
				std::cout << "Wallet looks good." << std::endl;
				orderBook.insertOrder(obe);
			}
			else {
				std::cout << "Insufficient funds." << std::endl;
			}
		}
		catch (const std::exception& e) {
			std::cout << "MerkelMain::enterBid Bad input" << std::endl;
		}
	}

	std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::printWallet() {
	// Print the wallet contents
	std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe() {
	// Go to the next timeframe
	std::cout << "Going to next time frame." << std::endl;
	std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
	std::cout << "Sales: " << sales.size() << std::endl;
	for (OrderBookEntry& sale : sales) {
		std::cout << "Sale price: " << sale.price << " amount: " << sale.amount << std::endl;
		if (sale.username == "simuser") {
			wallet.processSale(sale);
		}
	}

	currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption() {
	// Get the user's menu option
	int userOption = 0;
	std::string line;

	std::cout << "Type in 1-6" << std::endl;
	std::getline(std::cin, line);

	try {
		userOption = std::stoi(line);
	}
	catch (const std::exception& e) {}

	std::cout << "You chose: " << userOption << std::endl;
	return userOption;
}

void MerkelMain::processUserOption(int userOption) {
	// Process the user's menu option
	if (userOption == 0) {
		std::cout << "Invalid choice. Choose 1-6" << std::endl;
	}
	else if (userOption == 1) {
		printHelp();
	}
	else if (userOption == 2) {
		printMarketStats();
	}
	else if (userOption == 3) {
		enterAsk();
	}
	else if (userOption == 4) {
		enterBid();
	}
	else if (userOption == 5) {
		printWallet();
	}
	else if (userOption == 6) {
		gotoNextTimeframe();
	}
}
