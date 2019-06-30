/*
** EPITECH PROJECT, 2018
** CPP_plazza_2018
** File description:
** CCP_plazza_2018/tools/stringToWordArray.cpp
*/

#include "Plazza.hpp"

std::vector<int> computeLen(std::string str)
{
	std::vector<int> result;

	str = trim(str);
	if (str.compare("") == 0)
		return (result);
	result.push_back(0);
	for (unsigned int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ' || str[i] == '\t') {
			result.push_back(i);
			for (; (str[i] == ' ' || str[i] == '\t') && str[i] != '\0'; i++)
			if (i != '\0')
				continue;
			i -= 1;
		}
	}
	return (result);
}

std::vector<std::string> stringToWordArray(std::string str)
{
	std::vector<int> tab = computeLen(str);
	std::vector<std::string> result;
	unsigned int i = 0;

	str = trim(str);
	if (tab.size() != 0) {
		for (; i < tab.size() - 1; i++)
			result.push_back(trim(str.substr(tab[i], tab[i + 1] - tab[i])));
		result.push_back(trim(str.substr(tab[i], str.size())));
	}
	return (result);
}