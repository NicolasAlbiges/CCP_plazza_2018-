/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** include/PizzaFolder/PizzaAmericana.hpp
*/

#ifndef _PIZZA_AMERICANA_HPP_
#define _PIZZA_AMERICANA_HPP_

#include <thread>
#include "IPizza.hpp"

class PizzaAmericana : public IPizza
{
    public:
        PizzaAmericana(enum PizzaSize size) {
            _pizza.size = size;
            _pizza.type = Americana;
        }

        void cookingTime(float mul) final {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(3 * mul * 1000)));
        }

        Pizza_t getPizzaInfo(void) final {
            return _pizza;
        }

    private:
        Pizza_t _pizza;
};

#endif