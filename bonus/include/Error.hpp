/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/include/Error.hpp
*/

#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <vector>
#include <string>
#include "PizzaFolder/PizzaAmericana.hpp"
#include "PizzaFolder/PizzaFantasia.hpp"
#include "PizzaFolder/PizzaMargarita.hpp"
#include "PizzaFolder/PizzaRegina.hpp"

class Error
{
    public:
        Error(char **arg) {
            _arg = arg;
        };
        ~Error(void) {};

        void execute(void);
        std::vector<IPizza *> pizzaError(std::string cmd);

        float getMultiplier(void);
        int getCookers(void);
        int getStock(void);

    private:
        char **_arg;
        float _mul;
        int _cooks;
        int _stock;

        void recupMultiplier(char *);
        void recupCookers(char *);
        void recupStock(char *);
        int error_handling_pizza(std::string cmd);
        std::vector<IPizza *> parse_pizza(std::string cmd);
        std::vector<IPizza *> pushPizzaList(Pizza_t, std::vector<IPizza *>);
};

#endif