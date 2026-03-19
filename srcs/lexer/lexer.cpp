/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:15:46 by lucius            #+#    #+#             */
/*   Updated: 2026/03/19 15:05:20 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <regex>
#include <sstream>
#include <iostream>

#include "lexer/lexer.hpp"

std::vector<std::string> split_string(const std::string &code) {
	std::vector<std::string> words_vector;

	std::string::const_iterator it(code.begin());
	std::string recomposed_word = "";
	std::string special_characters = "{}();";

	while (it != code.end()) {
		while (std::isspace(*it))
			it++;
		recomposed_word += *it;
		it++;
		if (special_characters.find(*it) != std::string::npos || std::isspace(*it)) {
			words_vector.push_back(recomposed_word);
			recomposed_word.clear();
			if (special_characters.find(*it) != std::string::npos) {
				recomposed_word += *it;
				words_vector.push_back(recomposed_word);
				recomposed_word.clear();
			}
			it++;
		}
	}
	return (words_vector);
}

std::vector<Token> tokenizer(const std::string &code) {
	std::vector<Token> vector_token;
	std::stringstream ss(code);
	std::vector<std::string> word;

	// str into words
	word = split_string(code);
	std::cout << word.size() << std::endl;
	for (size_t i = 0; i < word.size(); i++) {
		std::cout << word[i] << std::endl;
	}
	// regex part
	//std::regex identifier_pattern("^[a-zA-Z_]\\w*$");
	//while (ss >> word) {
	//	//std::cout << i << ": " << word << std::endl;
	//	if (std::regex_match(word, identifier_pattern)) {
	//		std::cout << "In if condition: " << word << std::endl;
	//	}
	//}
	return (vector_token);
}