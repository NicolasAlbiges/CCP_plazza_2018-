/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/include/Kitchen.hpp
*/

#ifndef _KITCHEN_HPP_
#define _KITCHEN_HPP_

#include "ThreadPool.hpp"
#include "KitchenIPC.hpp"

class Kitchen
{
    public:
        Kitchen(float mul, int cooks, int stock, int port) {
            _ipc = new KitchenIPC(port);
            _pizzaQueue = new SafeQueue<IPizza *>;
            _ingredients = new Ingredients(stock);
            _pool = new ThreadPool(cooks, _pizzaQueue, _ingredients, mul);
        };
        ~Kitchen() {};

        void cookerJob();
        void run();
        void pointerFct(char *buffer);
        void end(char *buffer);
        void status(char *buffer);
        void pizza(char *buffer);
        void inactiveKitchen();
        void unpackPizza(Pizza_t);

    private:
        SafeQueue<IPizza *> *_pizzaQueue;
        ThreadPool *_pool;
        std::thread _inactiveThread;
        Ingredients *_ingredients;
        KitchenIPC *_ipc;
        float _multiplier;

        typedef struct command_s {
            const char *cmd;
            void (Kitchen::*cmd_name)(char *buffer);
        } command_t;
};

#endif