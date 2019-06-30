/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/include/Pizza.hpp
*/

#ifndef _IPIZZA_HPP_
#define _IPIZZA_HPP_

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

typedef struct Pizza_s {
    enum PizzaSize size;
    enum PizzaType type;
} Pizza_t;

class IPizza
{
    public:
        virtual ~IPizza(void) = default;

        virtual void cookingTime(float mul) = 0;
        virtual Pizza_t getPizzaInfo(void) = 0;
};

#endif