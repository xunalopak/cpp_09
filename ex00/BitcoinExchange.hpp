//
// Created by Romain on 26/03/2023.
//

#ifndef CPP09_BITCOINEXCHANGE_HPP
#define CPP09_BITCOINEXCHANGE_HPP

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

#define MAX_LINE 1000

class BitcoinExchange {

private:
	std::map<std::string, float> _data;

public:
	BitcoinExchange(std::string filename);
	BitcoinExchange(const BitcoinExchange &copy);
	~BitcoinExchange();
	BitcoinExchange &operator=(const BitcoinExchange &copy);

	void  getFile();
	bool  parseKey(std::string &key) const;
	bool  parseValue(std::string const &value) const;
	float findValue(std::string const &key);
	void  pricing(std::string const &key, std::string const &value);
	void  parseFile(std::string filename);

	class FileException : public std::exception {
		virtual const char *what() const throw();
	};
	class BadInputException : public std::exception {
		virtual const char *what() const throw();
	};

};


#endif //CPP09_BITCOINEXCHANGE_HPP
