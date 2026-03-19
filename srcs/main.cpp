/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:15:52 by lucius            #+#    #+#             */
/*   Updated: 2026/03/19 20:31:19 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "lexer/lexer.hpp"

int main(int ac, char *av[]) {
	if (ac < 1) {
		std::cout << "Usage: c_compile <file_to_compile>" << std::endl;
		return (1);
	}
	std::ifstream readed_file(av[1]);
	if (!readed_file.is_open()) {
		std::cerr << "Error: File couldn't be opened or dont exist" << std::endl;
		return (2);
	}
	std::ostringstream oss;
	oss << readed_file.rdbuf();
	std::string code = oss.str();
	readed_file.close();
	std::vector<Token> token_vector = tokenizer(code);
	for (Token t : token_vector) {
		std::cout << "value: " << t.value << " :: type: " << t.type << std::endl; 
	}
	return (0);
}