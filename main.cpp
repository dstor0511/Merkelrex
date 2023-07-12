/*
   main.cpp

   This is the main entry point of the program. It initializes the MerkelMain
   application and starts the program execution.

*/

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"

int main()
{
	MerkelMain app{}; // Create an instance of the MerkelMain application
	app.init(); // Initialize the application

	return 0;
}
