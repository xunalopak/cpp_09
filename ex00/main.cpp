//
// Created by Romain on 14/03/2023.
//

#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	try {
		//Premiere verification avant de lancer le programme
		if (ac != 2 || access(av[1], F_OK) == -1) {
			std::cout << "Error: could not open file (En gros c'est de la merde ce que tu envoie)" << std::endl;
			return (1);
		}

		std::map<std::string, float> _datamap;

		//Initialisation de la map en recuperant les donnees du fichier
		_datamap = parseFile(_datamap);

		//Lancement du programme
		bitcoinExchange(av[1], _datamap);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}