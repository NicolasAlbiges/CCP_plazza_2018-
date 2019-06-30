/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** include/PlazzaIPC.hpp
*/

#ifndef _PLAZZA_IPC_HPP_
#define _PLAZZA_IPC_HPP_

#include <vector>
#include <thread>
#include "tools.hpp"

class PlazzaIPC
{
    public:
        PlazzaIPC() {
            _sock = socket(AF_INET, SOCK_STREAM, 0);

            if (_sock == -1) {
                fprintf(stderr, "Error opening socket.\n");
                return;
            }
            _port = 1034;
            _sockAddr.sin_port = htons(_port);
            _sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
            _sockAddr.sin_family = AF_INET;
            while (bind(_sock, (struct sockaddr *)&_sockAddr, sizeof(struct sockaddr_in)) == -1) {
                if (errno == EADDRINUSE) {
                    _port = rand() % 40000 + 1024;
                    _sockAddr.sin_port = htons(_port);
                } else {
                    return;
                }
            }
            int opt = 1;
            setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
            if (listen(_sock, 1) < 0) {
                fprintf(stderr, "Listen faild.\n");
                return;
            }
            FD_ZERO(&_active_fd_set);
            FD_SET(0, &_active_fd_set);
            FD_SET(_sock, &_active_fd_set);
        }

        int selectIPC() {
            _read_fd_set = _active_fd_set;
            if (select(FD_SETSIZE, &_read_fd_set, NULL, NULL, NULL) < 0) {
                fprintf(stderr, "Select faild : %d   %d\n", errno, EBADF);
                return -1;
            }
            return 0;
        }

        int fdSetIPC(int fd) {
            if (FD_ISSET(fd, &_read_fd_set)) {
                return 0;
            }
            return -1;
        }

        void acceptKitchen() {
            int new_fd;
            size_t size = 0;

            size = sizeof(_sockAddr);
            if ((new_fd = accept(_sock, (struct sockaddr *)&_sockAddr, (socklen_t *)&size)) == -1) {
                fprintf(stderr, "Error accept.\n");
                return;
            }
            FD_SET(new_fd, &_active_fd_set);
            _fdKitchen.push_back(new_fd);
        }

        void endKitchen(int fd) {
            FD_CLR(fd, &_active_fd_set);
            for (unsigned int ct = 0; ct != _fdKitchen.size(); ct ++) {
                if (fd == _fdKitchen[ct]) {
                    _fdKitchen.erase(_fdKitchen.begin() + ct);
                    close(fd);
                    return;
                }
            }
        }

        int isFdKitchen(int fd) {
            for (unsigned int ct = 0; ct != _fdKitchen.size(); ct ++)
                if (_fdKitchen[ct] == fd)
                    return 0;
            return 1;
        }

        void operator<<(const int recv) {
            _kitchenReceiver = recv;
        }

        void operator<<(const std::string &str) {
            dprintf(_kitchenReceiver, "%s\n", str.c_str());
        }

        char *operator>>(int fd) {
            char *buffer;
            FILE *filedes = fdopen(fd, "r");
                    
            if ((filedes != NULL && isFdKitchen(fd) == 0) || fd == 0) {
                buffer = my_getline(filedes);
                return buffer;
            }
            return (char *)"";
        }

        int getSockId() {
            return _sock;
        }

        int getPort() {
            return _port;
        }

        std::vector<int> getKitchenId() {
            return _fdKitchen;
        }

    private:
        int _sock;
        int _port;
        int _kitchenReceiver;
        fd_set _read_fd_set;
        fd_set _active_fd_set;
        std::vector<int> _fdKitchen;
        struct sockaddr_in _sockAddr;

};

#endif