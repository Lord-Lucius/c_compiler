/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:15:46 by lucius            #+#    #+#             */
/*   Updated: 2026/03/24 15:39:30 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <regex>
#include <string>
#include <vector>

#include "main.hpp"

std::vector<std::string> Lexer::split_string(const std::string &code) {

	std::string recomposed_word = "";
	std::string special_characters = "#<>{}();";
	std::string unrecognized_characters = "@\\`";

	for (char c : code) {
		if (unrecognized_characters.find(c) != std::string::npos)
			throw UnrecognizedCharacterException();
		if (!std::isspace(c) && special_characters.find(c) == std::string::npos)
			recomposed_word += c;
		if (special_characters.find(c) != std::string::npos ||
			std::isspace(c)) {
			if (recomposed_word.length() > 1 &&
				std::isdigit(recomposed_word[0]) &&
				std::isalpha(recomposed_word[1]))
				throw NoneAlphaCharacterException();
			if (!recomposed_word.empty())
				_wordsOutOfCode.push_back(recomposed_word);
			if (special_characters.find(c) != std::string::npos)
				_wordsOutOfCode.push_back(std::string(1, c));
			recomposed_word.clear();
		}
	}
	return (_wordsOutOfCode);
}

Lexer::Lexer(const std::string &code) {
	// Patterns
	std::regex keyword_pattern("^(int|float|if|while|for|return)$");
	std::regex identifier_pattern(
		"^[a-zA-Z_][a-zA-Z0-9_]*$"); // means name ( identify the function )
	std::regex constant_pattern("^[0-9]+(\\.[0-9]+)?$");
	std::regex operator_pattern("^(\\+|-|\\*|/|=|==)$");
	std::regex open_delimiter_pattern("[\\{\\[\\(]$");
	std::regex close_delimiter_pattern("^[\\}\\]\\)]$");
	std::regex semicolon_pattern(";$");

	// str into words
	split_string(code);

	for (std::string w : _wordsOutOfCode) {
		if (std::regex_match(w, keyword_pattern))
			_tokens.push_back(Token({w, "KEYWORD"}));
		else if (std::regex_match(w, identifier_pattern))
			_tokens.push_back(Token({w, "IDENTIFIER"}));
		else if (std::regex_match(w, constant_pattern))
			_tokens.push_back(Token({w, "CONSTANT"}));
		else if (std::regex_match(w, operator_pattern))
			_tokens.push_back(Token({w, "OPERATOR"}));
		else if (std::regex_match(w, open_delimiter_pattern))
			_tokens.push_back(Token({w, "OPEN_DELIMITER"}));
		else if (std::regex_match(w, close_delimiter_pattern))
			_tokens.push_back(Token({w, "CLOSE_DELIMITER"}));
		else if (std::regex_match(w, semicolon_pattern))
			_tokens.push_back(Token({w, "SEMICOLON"}));
		else
			_tokens.push_back(Token({w, "UNKNOWN"}));
	}
}

std::vector<Token> Lexer::getTokenVector(void) { return _tokens; }
