/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/main.cpp
*/

#include "Plazza.hpp"

void help(void)
{
    std::cerr << HELP << std::endl;
    exit(84);
}

void execution(Error *err)
{
    Plazza *plazza = new Plazza(err->getMultiplier(), err->getCookers(), err->getStock());
    std::vector<Pizza_t> pizza_list;

    plazza->run(err);
}

int main(int ac, char **av)
{
    Error *err;

    if (ac != 4)
        help();
    err = new Error(av);
    err->execute();
    execution(err);
}