/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/src/Error.cpp
*/

#include "Plazza.hpp"

void Error::recupMultiplier(char *mul)
{
    std::string tmp(mul);
    int point = 0;

    for (char c : tmp) {
        if ((c < '0' || c > '9') && c != '.') {
            std::cerr << "Multiplier must be a valid float" << std::endl;
            exit(84);
        }
        c == '.' ? point += 1 : 0;
    }
    if (point > 1) {
        std::cerr << "Multiplier must be a valid float" << std::endl;
        exit(84);
    }
    try {
        _mul = std::atof(mul);
    } catch (std::exception &error) {
        std::cerr << "Multiplier must be a valid float" << std::endl;
        exit(84);
    }
    if (_mul <= 0) {
        std::cerr << "Multiplier must be greater then zero" << std::endl;
        exit(84);
    }
}

void Error::recupCookers(char *cook)
{
    std::string tmp(cook);

    for (char c : tmp) {
        if (c < '0' || c > '9') {
            std::cerr << "Cooks must be a valid integer" << std::endl;
            exit(84);
        }
    }
    try {
        _cooks = std::atoi(cook);
    } catch (std::exception &error) {
        std::cerr << "Cooks must be a valid integer" << std::endl;
        exit(84);
    }
    if (_cooks <= 0) {
        std::cerr << "Cooks must be greater then zero" << std::endl;
        exit(84);
    }
}

void Error::recupStock(char *stock)
{
    std::string tmp(stock);

    for (char c : tmp) {
        if (c < '0' || c > '9') {
            std::cerr << "Stock must be a valid integer" << std::endl;
            exit(84);
        }
    }
    try {
        _stock = std::atoi(stock);
    } catch (std::exception &error) {
        std::cerr << "Stock must be a valid integer" << std::endl;
        exit(84);
    }
    if (_stock <= 0) {
        std::cerr << "Stock must be greater then zero" << std::endl;
        exit(84);
    }
}

void Error::execute(void)
{
    this->recupMultiplier(_arg[1]);
    this->recupCookers(_arg[2]);
    this->recupStock(_arg[3]);
}

int Error::error_handling_pizza(std::string cmd)
{
    char sep[] = " \t";
    std::vector<std::string> sep_cmd;
    std::vector<std::string> type_size = {"regina", "margarita", "americana", "fantasia", "S", "M", "L", "XL", "XXL"};
    int same = 0;

    sep_cmd = word_array(cmd, sep);
    std::transform(sep_cmd[0].begin(), sep_cmd[0].end(), sep_cmd[0].begin(), ::tolower);
    if (sep_cmd.size() != 3)
        return 84;
    for (unsigned int ct = 0; ct != 4; ct ++)
        if (type_size[ct] == sep_cmd[0])
            same ++;
    for (unsigned int ct = 3; ct != type_size.size(); ct ++)
        if (type_size[ct] == sep_cmd[1])
            same ++;
    if (same != 2 || sep_cmd[2].length() == 1 || sep_cmd[2].length() > 3 || sep_cmd[2][0] != 'x' || isdigit(sep_cmd[2][1]) != true || sep_cmd[2][1] == '0')
        return 84;
    if (sep_cmd[2].length() == 3 && isdigit(sep_cmd[2][2]) == false)
        return 84;
    return 0;
}

std::vector<IPizza *> Error::pushPizzaList(Pizza_t pizza, std::vector<IPizza *> pizzaList)
{
    switch (pizza.type) {
        case Regina:
            pizzaList.push_back(new PizzaRegina(pizza.size));
            break;
        case Margarita:
            pizzaList.push_back(new PizzaMargarita(pizza.size));
            break;
        case Americana:
            pizzaList.push_back(new PizzaAmericana(pizza.size));
            break;
        default:
            pizzaList.push_back(new PizzaFantasia(pizza.size));
            break;
    }
    return pizzaList;
}

std::vector<IPizza *> Error::parse_pizza(std::string cmd)
{
    char sep[] = " \t";
    std::vector<std::string> sep_cmd = word_array(cmd, sep);
    int nbr = std::atoi(sep_cmd[2].substr(1).c_str());
    std::vector<std::string> type_str= {"regina", "margarita", "americana", "fantasia"};
    std::vector<std::string> size_str = {"S", "M", "L", "XL", "XXL"};
    std::vector<PizzaType> enum_type = {Regina, Margarita, Americana, Fantasia};
    std::vector<PizzaSize> enum_size = {S, M, L, XL, XXL};
    Pizza_t pizza;
    std::vector<IPizza *> pizza_list;

    for (int ct_nbr = 0; ct_nbr != nbr; ct_nbr ++) {
        for (unsigned int ct = 0; ct != enum_type.size(); ct++)
            if (type_str[ct] == sep_cmd[0])
                pizza.type = enum_type[ct];
        for (unsigned int ct = 0; ct != enum_size.size(); ct++)
            if (size_str[ct] == sep_cmd[1])
                pizza.size = enum_size[ct];
        pizza_list = pushPizzaList(pizza, pizza_list);
    }
    return pizza_list;
}

std::vector<IPizza *> Error::pizzaError(std::string command)
{
    char sep[] = ";";
    std::vector<std::string> sep_cmd;
    std::vector<std::vector<IPizza *>> pizza;
    std::vector<IPizza *> pizza_list;

    sep_cmd = word_array(command, sep);
    for (unsigned int ct = 0; ct != sep_cmd.size(); ct ++) {
        if (error_handling_pizza(sep_cmd[ct]) != 84) {
            pizza.push_back(parse_pizza(sep_cmd[ct]));
        } else
            std::cerr << "BAD ARGUMENT" << std::endl;
    }
    for (unsigned int ct_nbr = 0; ct_nbr != pizza.size(); ct_nbr ++) {
        for (unsigned int ct = 0; ct != pizza[ct_nbr].size(); ct ++) {
            pizza_list.push_back(pizza[ct_nbr][ct]);
        }
    }
    return pizza_list;
}

float Error::getMultiplier(void)
{
    return _mul;
}

int Error::getCookers(void)
{
    return _cooks;
}

int Error::getStock(void)
{
    return _stock;
}