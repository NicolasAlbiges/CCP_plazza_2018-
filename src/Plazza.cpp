/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/src/Plazza.cpp
*/

#include "Plazza.hpp"

int Plazza::getFdServer()
{
    return _ipc->getSockId();
}

int is_fd_data_sock(int fd, std::vector<int> fd_kitchen)
{
    for (unsigned int ct = 0; ct != fd_kitchen.size(); ct ++)
    if (fd == fd_kitchen[ct])
        return 0;
    return -1;
}

void Plazza::status(int fd, char *buffer)
{
    char op[] = " \n\t\r";
    std::vector<std::string> arr = word_array(buffer, op);

    printf("\nStatus of Kitchen Id %d :\n", fd);
    printf("  Number of Pizza waiting : %d\n", atoi(arr[1].c_str()));
    printf("  Number of Pizza being cooked : %d\n", atoi(arr[2].c_str()));
    printf("  Ingredients :\n");
    printf("    Tomato : %d\n", atoi(arr[3].c_str()));
    printf("    Gruyere : %d\n", atoi(arr[4].c_str()));
    printf("    Ham : %d\n", atoi(arr[5].c_str()));
    printf("    Mushroom : %d\n", atoi(arr[6].c_str()));
    printf("    Steak : %d\n", atoi(arr[7].c_str()));
    printf("    Eggplant : %d\n", atoi(arr[8].c_str()));
    printf("    Goat cheese : %d\n", atoi(arr[9].c_str()));
    printf("    Chief love : %d\n\n", atoi(arr[10].c_str()));
}

void Plazza::end(int fd, char *buffer)
{
    (void)buffer;
    _ipc->endKitchen(fd);
}

void Plazza::pointerFct(int fd, char *buffer)
{
    command_t const arr_cmd[2] = {{"STATUS", &Plazza::status}, {"END", &Plazza::end}};
    char op[] = " \n\t\r";
    std::vector<std::string> arr = word_array(buffer, op);

    for (int ct = 0; ct != 2; ct ++) {
        if (arr[0] == arr_cmd[ct].cmd) {
            (this->*arr_cmd[ct].cmd_name)(fd, buffer);
            return;
        }
    }
    return;
}

void Plazza::endKitchen(void)
{
    while (_ipc->getKitchenId().size() != 0) {
        *_ipc << _ipc->getKitchenId()[_ipc->getKitchenId().size() - 1];
        *_ipc << std::string("END");
        pointerFct(_ipc->getKitchenId()[_ipc->getKitchenId().size() - 1], (char*)"END\n");
    }
}

void Plazza::createKitchen(void)
{
    pid_t pid = fork();
    Kitchen *kitchen;

    if (pid == 0) {
        kitchen = new Kitchen(_mul, _cooks, _stock, _ipc->getPort());
        kitchen->run();
    }
}

void Plazza::readKitchen(int fd, char *buffer)
{
    if (fd == 0)
        return;
    pointerFct(fd, buffer);
    free(buffer);
}

std::string Plazza::packPizza(Pizza_t pizza)
{
    std::vector<std::string> type_str = {"regina", "margarita", "americana", "fantasia"};
    std::vector<std::string> size_str = {"S", "M", "L", "XL", "XXL"};
    std::vector<PizzaType> enum_type = {Regina, Margarita, Americana, Fantasia};
    std::vector<PizzaSize> enum_size = {S, M, L, XL, XXL};
    std::string type;
    std::string size;
    std::string piz = "PIZZA ";

    for (unsigned int ct = 0; ct != enum_type.size(); ct++)
        if (pizza.type == enum_type[ct])
            type = type_str[ct];
    for (unsigned int ct = 0; ct != enum_size.size(); ct++)
        if (pizza.size == enum_size[ct])
            size = size_str[ct];
    piz = piz + type + " " + size;
    return piz;
}

int Plazza::algorithmBrowseKitchen(Pizza_t pizza)
{
    FILE *filedes = NULL;
    char *buffer;
    char op[] = " \n\t\r";
    int min = _cooks * 2;
    int sendFd = -1;
    std::vector<std::string> arr;

    for (unsigned int ct = 0; ct != _ipc->getKitchenId().size(); ct ++) {
        *_ipc << _ipc->getKitchenId()[ct];
        *_ipc << std::string("STATUS");
        filedes = fdopen(_ipc->getKitchenId()[ct], "r");
        if (filedes != NULL) {
            buffer = my_getline(filedes);
        }
        if (buffer != NULL) {
            arr = word_array(buffer, op);
            if (arr[0].compare("END") == 0)
                continue;
            if ((atoi(arr[1].c_str()) + atoi(arr[2].c_str())) < min) {
                min = (atoi(arr[1].c_str()) + atoi(arr[2].c_str()));
                sendFd = _ipc->getKitchenId()[ct];
            }
        }
    }
    if (sendFd != -1) {
        *_ipc << sendFd;
        *_ipc << packPizza(pizza).c_str();
        return 1;
    }
    return 0;
}

void Plazza::algorithm(void)
{
    if (_ipc->getKitchenId().size() == 0) {
        createKitchen();
        return;
    }
    for (unsigned int ct = 0; ct != _pizza_list.size(); ct ++) {
        if (algorithmBrowseKitchen(_pizza_list[ct]->getPizzaInfo()) == 0) {
            createKitchen();
            return;
        }
        _pizza_list.erase(_pizza_list.begin() + ct);
        ct = -1;
    }
}

void Plazza::readClient(int fd, char *buffer, Error *err)
{
    if (fd != 0)
        return;
    if (std::string(buffer) == "status") {
        if (_ipc->getKitchenId().size() == 0) {
            printf("No kitchen open\n");
            return;
        }
        for (unsigned int ct = 0; ct != _ipc->getKitchenId().size(); ct ++) {
            *_ipc << _ipc->getKitchenId()[ct];
            *_ipc << std::string("STATUS");
        }
    } else {
        _pizza_list = err->pizzaError(buffer);
        if (_pizza_list.size() != 0)
            algorithm();
    }
    free(buffer);
}

void Plazza::run(Error *err)
{
    int fd = 0;
    char *buffer;

    while (1) {
        if (_ipc->selectIPC() == -1)
            return;
        for (fd = FD_SETSIZE; fd > -1; fd --) {
            if (_ipc->fdSetIPC(fd) == 0) {
                if (fd == _ipc->getSockId()) {
                    _ipc->acceptKitchen();
                    algorithm();
                } else {
                    buffer = *_ipc >> fd;
                    if (buffer == NULL) {
                        endKitchen();
                        return;
                    } else if (strcmp(buffer, "") != 0) {
                        readClient(fd, buffer, err);
                        readKitchen(fd, buffer);
                    }
                }
            }
        }
    }
}