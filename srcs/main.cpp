/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:15:52 by lucius            #+#    #+#             */
/*   Updated: 2026/03/24 15:39:30 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

#include "main.hpp"

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
		std::string code = oss.str();
		readed_file.close();

		std::vector<Token> token_vector = Lexer(code).getTokenVector();
		for (Token t : token_vector) {
			std::cout << t.value << "::" << t.type << std::endl;
		}
	} catch (std::ios::failure) {
		std::cout << "Error: ios error" << std::endl;
	} catch (Lexer::UnrecognizedCharacterException &u) {
		std::cout << u.what() << std::endl;
	} catch (Lexer::NoneAlphaCharacterException &n) {
		std::cout << n.what() << std::endl;
	} catch (...) {
		std::cout << "Error: Unknown error occured" << std::endl;
	}
	return (0);
}