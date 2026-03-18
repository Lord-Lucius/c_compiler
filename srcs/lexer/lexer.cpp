#include <regex>
#include <sstream>
#include <iostream>

#include "lexer/lexer.hpp"

std::vector<std::string> split_code(const std::string &code) {
	std::vector<std::string> words_vector;

	
}

std::vector<Token> tokenizer(const std::string &code) {
	std::vector<Token> vector_token;
	std::stringstream ss(code);
	std::string word;

	// regex part
	std::regex identifier_pattern("^[a-zA-Z_]\\w*$");
	while (ss >> word) {
		//std::cout << i << ": " << word << std::endl;
		if (std::regex_match(word, identifier_pattern)) {
			std::cout << "In if condition: " << word << std::endl;
		}
	}
	return (vector_token);
}