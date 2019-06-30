/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** B4-Concurrent_Programming/CCP_plazza_2018/include/ThreadPool.hpp
*/

#ifndef _THREADPOOL_HPP_
#define _THREADPOOL_HPP_

#include <vector>
#include <thread>
#include "SafeQueue.hpp"
#include "Ingredients.hpp"

class ThreadPool
{
    public:
        ThreadPool(int cooks, SafeQueue<IPizza *> *pizzaQueue, Ingredients *ingredients, float mul) {
            _stop = false;
            _multiplier = mul;
            _pizzaQueue = pizzaQueue;
            _ingredients = ingredients;
            for (int i = 0; i < cooks; i += 1) {
                _cookers.push_back(std::thread([this](){cookerJob();}));
            }
        }

        void cookerJob() {
            IPizza *pizzaTmp;

            while (_stop == false) {
                printf("Ready To Work !\n");
                pizzaTmp = _pizzaQueue->pop();
                while (_ingredients->doPizza(pizzaTmp->getPizzaInfo()) == false);
                pizzaTmp->cookingTime(_multiplier);
                _pizzaQueue->finishCook(pizzaTmp->getPizzaInfo());
            }
        }

        void stopPool(void) {
            _stop = true;
        }


    private:
        std::vector<std::thread> _cookers;
        SafeQueue<IPizza *> *_pizzaQueue;
        Ingredients *_ingredients;
        float _multiplier;
        bool _stop;
};

#endif