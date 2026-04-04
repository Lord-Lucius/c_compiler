/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 09:53:31 by luluzuri          #+#    #+#             */
/*   Updated: 2026/04/01 23:04:11 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

#pragma region Exception

class CustomException : public std::exception {
	protected:
		std::string _message;

	public:
		CustomException(const std::string &msg) : _message("Error: " + msg) {}

		const char *what() const noexcept override { return _message.c_str(); }
};

#pragma endregion

#pragma region UtilFunctions

#pragma endregion