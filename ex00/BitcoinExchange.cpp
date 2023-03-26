//
// Created by Romain on 26/03/2023.
//

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string filename) {
	getFile();
	parseFile(filename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {
	*this = copy;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) {
	if (this != &copy)
		this->_data = copy._data;
	return *this;
}

void BitcoinExchange::getFile(){
	std::ifstream 	file("data.csv");
	std::string 	line;
	float 			nb;
	int 			operatorPos;

	if (!file.is_open())
		throw FileException();
	while (getline(file, line)){
		if (line != "date,exchange_rate")
		{
			operatorPos = line.find(',');
			if (operatorPos == -1)
				throw BadInputException();
			std::istringstream(line.substr(operatorPos + 1, line.length())) >> nb;
			this->_data[line.substr(0, operatorPos)] = nb;
		}
	}
}

bool   BitcoinExchange::parseKey(std::string &key) const
{
	char buffer [80];
	const char *str = key.c_str();
	struct tm tm;
	char *end = strptime(str, "%Y-%m-%d", &tm);
	if (end == NULL || *end != '\0' || !strftime(buffer,80,"%Y-%m-%d",&tm))
	{
		std::cerr << "Error: bad input => " << key << "\n";
		return false;
	}
	return true;
}

bool  BitcoinExchange::parseValue(std::string const &value) const
{
	std::stringstream ss(value);
	if (value.find_first_not_of("0123456789.") != std::string::npos)
	{
		int num;
		ss >> num;
		if (num == 0)
			return true;
		if (num < 0){
			std::cerr << "Error: not a positive number." << std::endl;
			return false;
		}
		std::cerr << "Error: only digit accepted => " << value << std::endl;
		return false;
	}
	int converted;
	ss >> converted;
	if (converted > MAX_LINE){
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

float BitcoinExchange::findValue(std::string const &key){
	std::map<std::string, float>::iterator it;
	it = this->_data.find(key);
	if (it != this->_data.end())
		return it->second;

	it = this->_data.lower_bound(key);
	if (it == this->_data.end()){
		it--;
		return it->second;
	}
	return -1;
}

void BitcoinExchange::pricing(std::string const &key, std::string const &value) {
	std::stringstream ss(value);
	float result;
	ss >> result;
	if (result == -0)
		result = 0;
	std::cout << key << " => " << result << " = " << findValue(key) << std::endl;
}

void BitcoinExchange::parseFile(std::string filename) {
	std::ifstream 	file(filename);
	std::string 	line, key, date, value;
	size_t 			operatorPos;

	std::getline(file, line);
	while (!file.eof()){
		std::getline(file, line);
		operatorPos = line.find(" | ");
		if (operatorPos != std::string::npos){
			key = line.substr(0, operatorPos);
			if (parseKey(key)){
				value = line.substr(operatorPos + 3, line.find('\n'));
				if (parseValue(value))
					pricing(key, value);
			}
		}
		else
			std::cerr << "Error: bad input => " << line << "\n";
	}
}

const char *BitcoinExchange::FileException::what() const throw() {
	return "File couldn't be opened (en gros ça marche pas)";
}

const char *BitcoinExchange::BadInputException::what() const throw() {
	return "Bad input in file please check it (c'est pas mieux que le précédent)";
}
