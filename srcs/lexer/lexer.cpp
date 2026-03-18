#include <cctype>
#include <regex>
#include <sstream>
#include <iostream>

#include "lexer/lexer.hpp"

std::vector<std::string> split_string(const std::string &code) {
	std::vector<std::string> words_vector;

	std::string::const_iterator it(code.begin());
	std::string recomposed_word = "";
	std::string special_character = "{}();";

	while (it != code.end()) {
		while (std::isspace(*it) || std::isblank(*it))
			*it++;
		if (special_character.find(*it) != std::string::npos) {
			recomposed_word += *it;
		}
		else {
			while (std::isalnum(*it)) {
				recomposed_word += *it;
				*it++;
			}
		}
		if (!recomposed_word.empty()) {
			std::cout << recomposed_word << std::endl;
			words_vector.push_back(recomposed_word);
		}
		recomposed_word.clear();
		it++;
	}
	return (words_vector);
}

std::vector<Token> tokenizer(const std::string &code) {
	std::vector<Token> vector_token;
	std::stringstream ss(code);
	std::string word;

	// str into words
	split_string(code);
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