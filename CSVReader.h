#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <vector>

/** The CSVReader class is responsible for reading a CSV file and converting it into a vector of OrderBookEntry objects. */
class CSVReader
{

public:
	CSVReader();

	/** Read the CSV file and convert it into a vector of OrderBookEntry objects.
	 * @param csvFilename The filename of the CSV file to be read.
	 * @return A vector of OrderBookEntry objects representing the data from the CSV file.
	 */
	static std::vector<OrderBookEntry> readCSV(std::string csvFilename);

	/** Tokenize a CSV line into individual tokens.
	 * @param csvLine The CSV line to be tokenized.
	 * @param separator The character used as a separator in the CSV line.
	 * @return A vector of strings representing the tokens extracted from the CSV line.
	 */
	static std::vector<std::string> tokenise(std::string csvLine, char separator);

	/** Convert a vector of strings to an OrderBookEntry object.
	 * @param tokens The vector of strings representing the tokens of an OrderBookEntry.
	 * @return An OrderBookEntry object created from the provided tokens.
	 */
	static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);

	/** Convert strings representing individual attributes of an OrderBookEntry to an OrderBookEntry object.
	 * @param priceString The string representing the price of the OrderBookEntry.
	 * @param amountString The string representing the amount of the OrderBookEntry.
	 * @param timestamp The string representing the timestamp of the OrderBookEntry.
	 * @param product The string representing the product of the OrderBookEntry.
	 * @param orderType The OrderBookType of the OrderBookEntry.
	 * @return An OrderBookEntry object created from the provided attribute strings.
	 */
	static OrderBookEntry stringsToOBE(std::string priceString, std::string amountString,
									   std::string timestamp, std::string product,
									   OrderBookType orderType);
};
