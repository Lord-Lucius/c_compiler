/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:53:31 by luluzuri          #+#    #+#             */
/*   Updated: 2026/03/21 12:03:19 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <exception>

#pragma region Exception
class CustomException {
	public:
		class NoneAlphaCharacterException : public std::exception {
				const char *what() const noexcept {
					return "Error: First character is not alpha";
				}
		};

		class UnrecognizedCharacterException : public std::exception {
				const char *what() const noexcept {
					return "Error: Unrecognized character";
				}
		};
};
#pragma endregion

#pragma region Lexer
struct Token {
		std::string value;
		std::string type;
};

std::vector<Token> tokenizer(const std::string &code);
#pragma endregion

#pragma region Parser

#pragma endregion