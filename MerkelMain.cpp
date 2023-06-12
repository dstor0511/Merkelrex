#include "MerkelMain.h"
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <vector>

/*This is the constructor function*/
MerkelMain::MerkelMain() {};

/** This function will initiate the program (sim)*/
void MerkelMain::init() {
	int input;
	currentTime = orderBook.getEarliestTime();
	while (true) {
		printMenu();
		input = getUserOption();
		processUserOption(input);
	}
};

/*This function will display all the menu options*/
void MerkelMain::printMenu() {
	// 1 print help
	std::cout << "1: Print help " << std::endl;
	// 2 print exchange stats
	std::cout << "2: Print exchange stats" << std::endl;
	// 3 make an offer
	std::cout << "3: Make an offer " << std::endl;
	// 4 make a bid
	std::cout << "4: Make a bid " << std::endl;
	// 5 print wallet
	std::cout << "5: Print wallet " << std::endl;
	// 6 continue
	std::cout << "6: Continue " << std::endl;

	std::cout << "============== " << std::endl;

	std::cout << "Current Time is: " << currentTime << std::endl;
}

/*This function will handle the help menu*/
void MerkelMain::printHelp() {
	std::cout << "Help - your aim is to make money. Analyze the market and make "
	          "bids and offers. "
	          << std::endl;
}

/*This function will handle the market stats*/
void MerkelMain::printMarketStats() {
	for (std::string const &p : orderBook.getKnownProducts()) {
		std::cout << "Product: " << p << std::endl;
		std::vector<OrderBookEntry> entries = orderBook.getOrders(
		        OrderBookType::ask, p, currentTime);
		std::cout << "Asks for product seen: " << entries.size() << std::endl;
		std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
		std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
	}
	// std::cout << "Order Book Contains: " << orders.size() << " entries." <<
	// std::endl;

	// unsigned int bids = 0;
	// unsigned int asks = 0;

	// for (OrderBookEntry &e : orders)
	// {
	// 	if (e.orderType == OrderBookType::ask)
	// 	{
	// 		asks++;
	// 	}
	// 	if (e.orderType == OrderBookType::bid)
	// 	{
	// 		bids++;
	// 	}
	// }
	// std::cout << "Asks: " << asks << "--Bids: " << bids << std::endl;
}

/*This function will handle the offers*/
void MerkelMain::enterAsk() {
	std::cout << "Mark and ask - enter the amount: product,price,amount, eg ETH/BTC,200,0.5 " << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::cout << "You typed: " << input << std::endl;
}

/*This function will handle the bids*/
void MerkelMain::enterBid() {
	std::cout << "Make a bid - enter the amount" << std::endl;
}

/*This function will handle the wallet*/
void MerkelMain::printWallet() {
	std::cout << "Your wallet is empty. " << std::endl;
}

/*This function will handle the time frame*/
void MerkelMain::gotoNextTimeframe() {
	std::cout << "Going to next time frame. " << std::endl;
	currentTime = orderBook.getNextTime(currentTime);
}

/*This function will receive and return the user input in response to the menu
 * option selected*/
int MerkelMain::getUserOption() {
	int userOption;

	std::cout << "Type in 1-6" << std::endl;
	std::cin >> userOption;
	std::cout << "You chose: " << userOption << std::endl;
	return userOption;
}

/*This function will handle userOption and execute the desired functionality*/
void MerkelMain::processUserOption(int userOption) {

	if (userOption == 0) {
		/*bad input*/
		std::cout << "Invalid choice. Choose 1-6" << std::endl;
	}
	if (userOption == 1) {
		/*execution of the printHelp function*/
		printHelp();
	}
	if (userOption == 2) {
		/*execution of the printMarketStats function*/
		printMarketStats();
	}
	if (userOption == 3) {
		/*execution of the enterOffer function*/
		enterAsk();
	}
	if (userOption == 4) {
		/*execution of the enterBid function*/
		enterBid();
	}
	if (userOption == 5) {
		/*execution of the printWallet function*/
		printWallet();
	}
	if (userOption == 6) {
		/*execution of the gotoNextTimeframe function*/
		gotoNextTimeframe();
	}
}