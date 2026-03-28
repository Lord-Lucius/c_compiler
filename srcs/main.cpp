/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:15:52 by lucius            #+#    #+#             */
/*   Updated: 2026/03/28 14:00:38 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"

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
		Parser parser = Parser();
		std::vector<Token *> tokens = lexer.tokenize();
		for (Token *t : tokens) {
			std::cout << t->TYPE << " :: " << t->value << std::endl;
		}

		// Parsing part
		Program *program = parser.parse(tokens);

		for (Token *t : tokens)
			delete t;
		delete program;
	} catch (std::ios::failure) {
		std::cout << "Error: ios error" << std::endl;
		return (1);
	} catch (Lexer::UnrecognizedCharacterException &u) {
		std::cout << u.what() << std::endl;
		return (2);
	} catch (Lexer::NoneAlphaCharacterException &n) {
		std::cout << n.what() << std::endl;
		return (3);
	} catch (...) {
		std::cout << "Error: Unknown error occured" << std::endl;
		return (4);
	}
	return (0);
}