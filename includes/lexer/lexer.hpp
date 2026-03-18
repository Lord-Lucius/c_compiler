/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucius <lucius@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 21:29:48 by lucius            #+#    #+#             */
/*   Updated: 2026/03/18 18:26:32 by lucius           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

// Basic lexer
struct Token {
	std::string value;
	std::string type;
};

std::vector<Token> tokenizer(const std::string &code);
