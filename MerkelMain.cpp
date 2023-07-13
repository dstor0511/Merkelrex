/*
   MerkelMain.cpp

   This file contains the implementation of the MerkelMain class, which represents
   the application itself. It handles user input, menu printing, and the execution
   of various functionalities.
*/

#include "MerkelMain.h"
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include "CandleStick.h"
#include <iostream>
#include <vector>
#include <limits> // Include the <limits> header

MerkelMain::MerkelMain()
{
	// Constructor implementation
}

void MerkelMain::init()
{
	int input;
	currentTime = orderBook.getEarliestTime();

	wallet.insertCurrency("BTC", 10);

	while (true)
	{
		printMenu();
		input = getUserOption();
		processUserOption(input);
	}
}

void MerkelMain::printMenu()
{
	// Print the menu options
	std::cout << "1: Print help" << std::endl;
	std::cout << "2: Print exchange stats" << std::endl;
	std::cout << "3: Print candlestck stats" << std::endl;
	std::cout << "4: Make an offer" << std::endl;
	std::cout << "5: Make a bid" << std::endl;
	std::cout << "6: Print wallet" << std::endl;
	std::cout << "7: Continue" << std::endl;
	std::cout << "============== " << std::endl;
	std::cout << "Current Time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
	// Print the help information
	std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers." << std::endl;
}

void MerkelMain::printMarketStats()
{
	// Print the market statistics
	for (std::string const &p : orderBook.getKnownProducts())
	{
		std::cout << "Product: " << p << std::endl;

		std::vector<OrderBookEntry> entriesask = orderBook.getOrders(OrderBookType::ask, p, currentTime);
		std::cout << "Asks for product seen: " << entriesask.size() << std::endl;
		std::cout << "Max ask: " << OrderBook::getHighPrice(entriesask) << std::endl;
		std::cout << "Min ask: " << OrderBook::getLowPrice(entriesask) << std::endl;
		std::cout << " " << std::endl;

		std::vector<OrderBookEntry> entriesbid = orderBook.getOrders(OrderBookType::bid, p, currentTime);
		std::cout << "Bids for product seen: " << entriesbid.size() << std::endl;
		std::cout << "Max bid: " << OrderBook::getHighPrice(entriesbid) << std::endl;
		std::cout << "Min bid: " << OrderBook::getLowPrice(entriesbid) << std::endl;
		std::cout << " " << std::endl;
	}
}

void MerkelMain::displayKnownProducts()
{
	// Display the known products
	std::vector<std::string> products = orderBook.getKnownProducts();
	for (std::string const &p : products)
	{
		std::cout << p << std::endl;
	}
}

// This function will print the candlestick stats
std::vector<Candlestick> MerkelMain::candleStickData()
{
	std::string orderTypeStr;
	std::string product;

	std::cout << "Enter order type (ask or bid): " << std::endl;
	std::getline(std::cin, orderTypeStr);

	displayKnownProducts();
	std::cout << "Enter product from above: " << std::endl;
	std::getline(std::cin, product);

	// get the first timestamp and push it into the vector
	std::vector<std::string> uniqueTimestamps;
	std::string currentTimestamp = orderBook.getEarliestTime();
	uniqueTimestamps.push_back(currentTimestamp);

	// loop over all entries to get the unique timestamps
	while (orderBook.getNextTime(currentTimestamp) > currentTimestamp)
	{
		currentTimestamp = orderBook.getNextTime(currentTimestamp);
		uniqueTimestamps.push_back(currentTimestamp);
	}

	std::cout << "Candlestick data for " << product << " " << orderTypeStr << std::endl;
	OrderBookType order = orderTypeStr == "ask" ? OrderBookType::ask : OrderBookType::bid;

	// create a vector of Candlestick objects
	std::vector<Candlestick> candlesticks;
	double openPrice = 0.0;
	double highestPrice = 0.0;
	double lowestPrice = std::numeric_limits<double>::max();
	double closePrice = 0.0;

	for (const std::string &timestamp : uniqueTimestamps)
	{
		std::vector<OrderBookEntry> entries = orderBook.getOrders(order, product, timestamp);

		double amount = 0.0;
		double price = 0.0;

		// loop over all entries for the current timestamp
		for (const OrderBookEntry &entry : entries)
		{
			if (entry.orderType == order && entry.product == product && entry.timestamp == timestamp)
			{
				if (entry.price > highestPrice)
				{
					highestPrice = entry.price;
				}
				if (entry.price < lowestPrice)
				{
					lowestPrice = entry.price;
				}

				amount += entry.amount;
				price += entry.price;
			}
		}
		openPrice = closePrice;
		double totalAmount = amount * price;
		closePrice = totalAmount / amount;

		Candlestick candlestick(timestamp, openPrice, highestPrice, lowestPrice, closePrice);
		candlesticks.push_back(candlestick);
	}

	// print the candlestick data
	for (const Candlestick &candlestick : candlesticks)
	{
		std::cout << "[ " << candlestick.candleTimestamp << " " << candlestick.candleOpenPrice << " " << candlestick.candleHighPrice
				  << " " << candlestick.candleLowPrice << " " << candlestick.candleClosingPrice << " ]" << std::endl;
	}

	return candlesticks;
}

void MerkelMain::enterAsk()
{
	// Handle entering an ask
	std::cout << "Mark and ask - enter the amount: product,price,amount, e.g., ETH/BTC,200,0.5" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

	if (tokens.size() != 3)
	{
		std::cout << "Bad input!" << input << "Please make sure you don't use spaces between the 3 values" << std::endl;
	}
	else
	{
		try
		{
			OrderBookEntry obe = CSVReader::stringsToOBE(
				tokens[1],
				tokens[2],
				currentTime,
				tokens[0],
				OrderBookType::ask);
			obe.username = "simuser";
			if (wallet.canFulfillOrder(obe))
			{
				std::cout << "Wallet looks good." << std::endl;
				orderBook.insertOrder(obe);
			}
			else
			{
				std::cout << "Insufficient funds." << std::endl;
			}
		}
		catch (const std::exception &e)
		{
			std::cout << "MerkelMain::enterAsk Bad input" << std::endl;
		}
	}

	std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::enterBid()
{
	// Handle entering a bid
	std::cout << "Make a bid - enter the amount: product,price,amount, e.g., ETH/BTC,200,0.5" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

	if (tokens.size() != 3)
	{
		std::cout << "Bad input!" << input << "Please make sure you don't use spaces between the 3 values" << std::endl;
	}
	else
	{
		try
		{
			OrderBookEntry obe = CSVReader::stringsToOBE(
				tokens[1],
				tokens[2],
				currentTime,
				tokens[0],
				OrderBookType::bid);

			obe.username = "simuser";
			if (wallet.canFulfillOrder(obe))
			{
				std::cout << "Wallet looks good." << std::endl;
				orderBook.insertOrder(obe);
			}
			else
			{
				std::cout << "Insufficient funds." << std::endl;
			}
		}
		catch (const std::exception &e)
		{
			std::cout << "MerkelMain::enterBid Bad input" << std::endl;
		}
	}

	std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::printWallet()
{
	// Print the wallet contents
	std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
	// Go to the next timeframe
	std::cout << "Going to next time frame." << std::endl;
	std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
	std::cout << "Sales: " << sales.size() << std::endl;
	for (OrderBookEntry &sale : sales)
	{
		std::cout << "Sale price: " << sale.price << " amount: " << sale.amount << std::endl;
		if (sale.username == "simuser")
		{
			wallet.processSale(sale);
		}
	}

	currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
	// Get the user's menu option
	int userOption = 0;
	std::string line;

	std::cout << "Type in 1-6" << std::endl;
	std::getline(std::cin, line);

	try
	{
		userOption = std::stoi(line);
	}
	catch (const std::exception &e)
	{
	}

	std::cout << "You chose: " << userOption << std::endl;
	return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
	// Process the user's menu option
	if (userOption == 0)
	{
		std::cout << "Invalid choice. Choose 1-6" << std::endl;
	}
	else if (userOption == 1)
	{
		printHelp();
	}
	else if (userOption == 2)
	{
		printMarketStats();
	}
	else if (userOption == 3)
	{
		candleStickData();
	}
	else if (userOption == 4)
	{
		enterAsk();
	}
	else if (userOption == 5)
	{
		enterBid();
	}
	else if (userOption == 6)
	{
		printWallet();
	}
	else if (userOption == 7)
	{
		gotoNextTimeframe();
	}
}
