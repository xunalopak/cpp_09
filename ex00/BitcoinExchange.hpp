//
// Created by Romain on 26/03/2023.
//

#ifndef CPP09_BITCOINEXCHANGE_HPP
#define CPP09_BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <map>
#include <unistd.h>

std::map<std::string, float> parseFile(std::map<std::string, float> _datamap);
void bitcoinExchange(std::string file, std::map<std::string, float> _datamap);


#endif //CPP09_BITCOINEXCHANGE_HPP
