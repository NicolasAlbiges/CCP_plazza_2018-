/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** include/PizzaFolder/PizzaRegina.hpp
*/

#ifndef _PIZZA_REGINA_HPP_
#define _PIZZA_REGINA_HPP_

#include <thread>
#include "IPizza.hpp"

class PizzaRegina : public IPizza
{
    public:
        PizzaRegina(enum PizzaSize size) {
            _pizza.size = size;
            _pizza.type = Regina;
        }

        void cookingTime(float mul) final {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(1 * mul * 1000)));
        }

        Pizza_t getPizzaInfo(void) final {
            return _pizza;
        }

    private:
        Pizza_t _pizza;
};

#endif