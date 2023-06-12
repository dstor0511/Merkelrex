/*Here we include the necessary contents into our library*/
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"

/*This is the main function that will run the program*/
int main()
{
	MerkelMain app{};
	app.init();

	// CSVReader::readCSV("20200317.csv");
	// std::vector<OrderBookEntry> orderBook = CSVReader::readCSV("20200317.csv");
	// std::cout << "read " << orderBook.size() << " orders" << std::endl;
}