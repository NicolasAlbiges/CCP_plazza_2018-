/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** include/PizzaFolder/PizzaFantasia.hpp
*/

#ifndef _PIZZA_FANTASIA_HPP_
#define _PIZZA_FANTASIA_HPP_

#include <thread>
#include "IPizza.hpp"

class PizzaFantasia : public IPizza
{
    public:
        PizzaFantasia(enum PizzaSize size) {
            _pizza.size = size;
            _pizza.type = Fantasia;
        }

        void cookingTime(float mul) final {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(4 * mul * 1000)));
        }

        Pizza_t getPizzaInfo(void) final {
            return _pizza;
        }

    private:
        Pizza_t _pizza;
};

#endif