/*
** EPITECH PROJECT, 2018
** CPP_plazza_2018
** File description:
** CCP_plazza_2018/tools/stringToWordArray.cpp
*/

#include "tools.hpp"

char *my_getline(FILE *stream)
{
    size_t size = 0;
    char *str = NULL;
    int readed = 0;

    readed = getline(&str, &size, stream);
    if (readed <= 0) {
        free(str);
        return (NULL);
    }
    str[readed - 1] = '\0';
    return (str);
}