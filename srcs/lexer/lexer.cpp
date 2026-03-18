#include <regex>
#include <sstream>
#include <iostream>

#include "lexer/lexer.hpp"

std::vector<Token> tokenizer(const std::string &code) {
	std::vector<Token> vector_token;
	std::stringstream ss(code);
	std::string word;

	// regex part
	std::regex identifier_pattern("[a-zA-z_]\\w*");
	while (ss >> word) {
		if (std::regex_match(word, identifier_pattern)) {
			std::cout << word << std::endl;
		}
	}
	return (vector_token);
}