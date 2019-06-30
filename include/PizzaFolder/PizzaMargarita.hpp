/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** include/PizzaFolder/PizzaMargarita.hpp
*/

#ifndef _PIZZA_MARGARITA_HPP_
#define _PIZZA_MARGARITA_HPP_

#include <thread>
#include "IPizza.hpp"

class PizzaMargarita : public IPizza
{
    public:
        PizzaMargarita(enum PizzaSize size) {
            _pizza.size = size;
            _pizza.type = Margarita;
        }

        void cookingTime(float mul) final {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(2 * mul * 1000)));
        }

        Pizza_t getPizzaInfo(void) final {
            return _pizza;
        }

    private:
        Pizza_t _pizza;
};

#endif