#include "CSVReader.h"
#include <fstream>
#include <iostream>

CSVReader::CSVReader() {}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename) {

    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;

    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {

            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            } catch (const std::exception &e) {
                std::cout << "CSVReader:: readCSV red " << entries.size() << " entries"
                          << std::endl;
            }
        }
    }

    std::cout << "CSVReader:: readCSV red " << entries.size() << " entries"
              << std::endl;
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine,
        char separator) {

    std::vector<std::string> tokens; // Vector to store the tokens

    signed int start,
           end; // Variables to keep track of token start and end positions

    std::string token; // Variable to store each token

    start = csvLine.find_first_not_of(
                separator, 0); // Find the first non-separator character in the line

    // Loop until the end of the line is reached
    do {
        end = csvLine.find_first_of(separator,
                                    start); // Find the next separator character
        // from the current start position

        // If no separator is found or the start and end positions are the same,
        // break the loop
        if (start == csvLine.length() || start == end)
            break;

        // If a separator is found, extract the token between start and end
        // positions
        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token); // Add the token to the vector

        start = end + 1; // Update the start position for the next iteration
    } while (end !=
             std::string::npos); // Continue until the end of the line is reached

    return tokens; // Return the vector of tokens
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {

    double price, amount;

    if (tokens.size() != 5) {
        std::cout << "Bad Line" << tokens[0] << std::endl;
        throw std::exception{};
    }

    try {
        // convert data types
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    } catch (const std::exception &e) {
        std::cout << "Bad float!" << tokens[3] << std::endl;
        std::cout << "Bad float!" << tokens[4] << std::endl;
        throw;
    };

    OrderBookEntry obe{price, amount, tokens[0], tokens[1],
                       OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}