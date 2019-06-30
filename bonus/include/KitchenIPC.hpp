/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** include/Kitchen_IPC.hpp
*/

#ifndef _KITCHEN_IPC_HPP_
#define _KITCHEN_IPC_HPP_

#include <vector>
#include <thread>
#include "tools.hpp"

class KitchenIPC
{
    public:
        KitchenIPC(int port) {
            _port = port;
            _sock = socket(AF_INET, SOCK_STREAM, 0);
            if (_sock == -1) {
                fprintf(stderr, "Error opening socket.\n");
                return;
            }
            _sockAddr.sin_port = htons(_port);
            _sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
            _sockAddr.sin_family = AF_INET;
            if (connect(_sock, (struct sockaddr *)&_sockAddr, sizeof(struct sockaddr_in)) == -1) {
                fprintf(stderr, "Connect failed.\n");
                return;
            }
        }

        void operator<<(const std::string &str) {
            dprintf(_sock, "%s\n", str.c_str());
        }

        char *operator>>(char *str) {
            FILE *fdKitchen = fdopen(_sock, "r");

            if (fdKitchen == NULL) {
                fprintf(stderr, "Filedesciptor nor valid in kitchen.\n");
            }
            str = my_getline(fdKitchen);
            return str;
        }

        int getSockId() {
            return _sock;
        }

    private:
        int _sock;
        int _port;
        struct sockaddr_in _sockAddr;
};

#endif