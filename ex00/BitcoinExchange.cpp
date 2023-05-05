//
// Created by Romain on 26/03/2023.
//

#include "BitcoinExchange.hpp"

std::map<std::string, float> parseFile(std::map<std::string, float> _datamap) {
	std::ifstream   infile;
	std::string     database;

	infile.open("./data.csv");
	while (!infile.eof())
	{
		infile >> database;
		std::string date = database.substr(0,10).erase(4,1).erase(6,1);
		float      rate = 0.0;
		std::stringstream convert;
		convert << database.substr(11);
		convert >> rate;
		_datamap.insert(std::make_pair(date,rate));
	}
	infile.close();
	return (_datamap);
}

int parsing(int year, int month, int day, std::string value, int valuebtc, std::string line) {
	size_t idx = line.find("|");
	if (line[idx + 1] != ' ' || line[idx - 1] != ' ')
	{
		std::cerr << "Error: Invalid pipe\n";
		return (-1);
	}

	if (line.substr(4,1) != "-" && line.substr(7,1) != "-")
	{
		std::cerr << "Error: Invalid date format\n";
		return (-1);
	}

	int count = 0;
	for (size_t i = 0; i < value.length(); i++)
	{
		if (value[0] == '.')
		{
			std::cerr << "Error: Invalid value format\n";
			return (-1);
		}
		if (value[i] == '.')
			count++;
		if (!(isdigit(value[i])) && value[i] != '.' && (count == 1 || count == 0))
		{
			std::cerr << "Error: Invalid value format\n";
			return (-1);
		}
	}

	int month_limits[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year < 2009 || month < 1 || month > 12)
	{
		std::cerr << "Error: Invalid date format\n";
		return (-1);
	}
	if (day > month_limits[month - 1] || day < 1)
	{
		std::cerr << "Error: Out of month range\n";
		return (-1);
	}
	if (valuebtc < 0.00 || valuebtc > 1000.00 )
	{
		std::cerr << "Error: Rate out of range\n";
		return (-1);
	}
	return (0);
}

void printOutput(std::string inputdate, float bitcoins, std::map<std::string, float> _datamap)
{
	std::map<std::string, float>::iterator itb = _datamap.begin();
	std::map<std::string, float>::iterator ite = _datamap.end();
	bool flag = false;

	for (; itb != ite; itb++) {
		if (itb->first == inputdate) {
			flag = true;
			break;
		}
	}
	if (flag) {
		char buffer[50];
		sprintf(buffer, "%.2f", bitcoins * itb->second);
		std::cout << inputdate.insert(4, "-").insert(7, "-") << " => " << bitcoins << " = " << buffer << "\n";
		flag = false;
	}
	else {
		ite = _datamap.lower_bound(inputdate);
		char buffer[50];
		sprintf(buffer, "%.2f", bitcoins * ite->second);
		std::cout << inputdate.insert(4, "-").insert(7, "-") << " => " << bitcoins << " = " << buffer << "\n";
	}
}

void bitcoinExchange(std::string file, std::map<std::string, float> _datamap) {
	std::ifstream infile;
	std::string line;

	infile.open(file.c_str());

	if (!infile.is_open()) {
		std::cerr << "Error: Could not open file\n";
		return ;
	}

	while (getline(infile, line)) {
		std::string date;
		int year, month, day = 0;
		std::stringstream y, m, d;

		y << line.substr(0, 4);
		y >> year;

		m << line.substr(5, 2);
		m >> month;

		d << line.substr(8, 2);
		d >> day;

		if (line.length() < 14) {
			std::cerr << "Error: Invalid format\n";
			continue;
		}

		std::string value = line.substr(13, line.find('\0'));

		float bitcoins = 0.00;
		std::stringstream bit;
		bit << value;
		bit >> bitcoins;

		std::ostringstream oss;
		if (month < 10 && day < 10)
			oss << year * 10 << month * 10 << day;
		else if (day < 10)
			oss << year << month * 10 << day;
		else if (month < 10)
			oss << year * 10 << month << day;
		else
			oss << year << month << day;

		date = oss.str();

		if (parsing(year, month, day, value, bitcoins, line) == 0)
			printOutput(date, bitcoins, _datamap);
	}
	infile.close();
}































