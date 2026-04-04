/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:15:52 by lucius            #+#    #+#             */
/*   Updated: 2026/04/02 00:34:22 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

#include "Lexer.hpp"

int main(int ac, char *av[]) {
	if (ac < 2) {
		std::cout << "Usage: c_compile <file_to_compile>" << std::endl;
		return (1);
	}
	std::string file_name;
	for (int i = 1; i < ac; i++) {
		std::string arg = av[i];
		if (arg[0] != '-') {
			file_name = arg;
			break;
		}
	}

	std::ifstream readed_file(file_name);
	if (!readed_file.is_open()) {
		std::cerr << "Error: File couldn't be opened or dont exist ( "
				  << file_name << " )" << std::endl;
		return (2);
	}

	try {
		std::ostringstream oss;
		oss << readed_file.rdbuf();
		std::string sourceCode = oss.str();
		readed_file.close();

		Lexer lexer(sourceCode);
		std::vector<Token *> &tokens = lexer.tokenize();

		std::cout << tokens.size() << std::endl;
		for (Token *t : tokens) {
			std::cout << tokenTypeToString(t->TYPE) << " :: " << t->value << std::endl;
		}

	} catch (std::ios::failure) {
		std::cout << "Error: ios error" << std::endl;
		return (1);
	} catch (CustomException &u) {
		std::cout << u.what() << std::endl;
		return (2);
	} catch (...) {
		std::cout << "Error: Unknown error occured" << std::endl;
		return (4);
	}
	return (0);
}
