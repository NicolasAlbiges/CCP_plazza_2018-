/*
** EPITECH PROJECT, 2018
** CPP_plazza_2018
** File description:
** CCP_plazza_2018/tools/trim.cpp
*/

#include "Plazza.hpp"

std::string trim(std::string str)
{
	std::string result = str;
	for (; result[0] == ' ' || result[0] == '\t'; result = result.substr(1));
	std::reverse(result.begin(), result.end());
	for (; result[0] == ' ' || result[0] == '\t'; result = result.substr(1));
	std::reverse(result.begin(), result.end());
	return (result);
}