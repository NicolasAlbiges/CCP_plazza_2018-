/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/include/plazza.hpp
*/

#ifndef _PLAZZA_HPP_
#define _PLAZZA_HPP_

#include <iostream>
#include "Kitchen.hpp"
#include "Error.hpp"
#include "tools.hpp"
#include "PlazzaIPC.hpp"

#define HELP "USAGE:\n\t./plazza m c stock\n\nDESCRIPTION:\n\t\
m\tmultiplier for the cooking time of the pizzas\n\tc\t\
number of cooks per kitchen\n\tstock\ttime in milliseconds, used by the \
kitchen stock to replace ingredients"

class Plazza
{
    public:
        Plazza(float mul, int cooks, int stock) {
            _mul = mul;
            _cooks = cooks;
            _stock = stock;
            _ipc = new PlazzaIPC();
        };
        ~Plazza(void) {};

        int getFdServer();
        int isFdKitchen(int fd);
        void readClient(int fd, char *buffer, Error *err);
        void readKitchen(int fd, char *buffer);
        void createKitchen();
        void run(Error *err);
        void pointerFct(int fd, char *buffer);
        void algorithm(void);
        int algorithmBrowseKitchen(Pizza_t pizza);
        std::string packPizza(Pizza_t pizza);
        void endKitchen(void);
        void end(int fd, char *buffer);
        void status(int fd, char *buffer);
        std::pair<int, std::vector<std::string>> status_kitchen(void);

        std::vector<Pizza_t> newCommand(std::vector<std::vector<Pizza_t>>);

    private:
        float _mul;
        int _cooks;
        int _stock;
        std::vector<IPizza *> _pizza_list;
        PlazzaIPC *_ipc;

        typedef struct command_s {
            const char *cmd;
            void (Plazza::*cmd_name)(int fd, char *buffer);
        } command_t;
};

#endif