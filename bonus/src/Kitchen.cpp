/*
** EPITECH PROJECT, 2018
** NWP_myftp_2018
** File description:
** CCP_plazza_2018/src/Kitchen.cpp
*/

#include "Plazza.hpp"

void Kitchen::pizzaAdd(Pizza_t pizza)
{
    switch (pizza.type) {
        case Regina:
            _pizzaQueue->push(new PizzaRegina(pizza.size));
            break;
        case Margarita:
            _pizzaQueue->push(new PizzaMargarita(pizza.size));
            break;
        case Americana:
            _pizzaQueue->push(new PizzaAmericana(pizza.size));
            break;
        default:
            _pizzaQueue->push(new PizzaFantasia(pizza.size));
            break;
    }
}

void Kitchen::pizza(char *buffer)
{
    std::vector<std::string> type_str= {"regina", "margarita", "americana", "fantasia"};
    std::vector<std::string> size_str = {"S", "M", "L", "XL", "XXL"};
    std::vector<PizzaType> enum_type = {Regina, Margarita, Americana, Fantasia};
    std::vector<PizzaSize> enum_size = {S, M, L, XL, XXL};
    char op[] = " \n\t\r";
    std::vector<std::string> arr = word_array(buffer, op);
    Pizza_t tmp;

    for (unsigned int ct = 0; ct != enum_type.size(); ct++) {
        if (type_str[ct] == arr[1])
            tmp.type = enum_type[ct];
    }
    for (unsigned int ct = 0; ct != enum_size.size(); ct++) {
        if (size_str[ct] == arr[2])
            tmp.size = enum_size[ct];
    }
    pizzaAdd(tmp);
}

void Kitchen::graph(char *buffer)
{
    (void)buffer;
    *_ipc << "GRAPH " + std::to_string(_pizzaQueue->getCooking());
}

void Kitchen::status(char *buffer)
{
    (void)buffer;
    *_ipc << "STATUS " + std::to_string(_pizzaQueue->getQueueSize()) + " " +
    std::to_string(_pizzaQueue->getCooking()) + " " + _ingredients->getIngredientList();
}

void Kitchen::end(char *buffer)
{
    (void)buffer;
    _pool->stopPool();
    _ingredients->Stop();
    _ingredients->_t.join();
    printf("End of Service for the Kitchen Id %d\n", _ipc->getSockId());
    *_ipc << std::string("END");
    exit (0);
}

void Kitchen::pointerFct(char *buffer)
{
    command_t const arr_cmd[4] = {{"PIZZA", &Kitchen::pizza}, {"STATUS", &Kitchen::status}, {"END", &Kitchen::end}, {"GRAPH", &Kitchen::graph}};
    char op[] = " \n\t\r";
    std::vector<std::string> arr = word_array(buffer, op);

    for (int ct = 0; ct != 4; ct ++) {
        if (arr[0] == arr_cmd[ct].cmd) {
            (this->*arr_cmd[ct].cmd_name)(buffer);
            return;
        }
    }
    return;
}

void Kitchen::inactiveKitchen()
{
    while (1) {
        sleep(1);
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _pizzaQueue->getInactive()).count() > 5
        && _pizzaQueue->getCooking() == 0 && _pizzaQueue->getQueueSize() == 0)
            break;
    }
    end((char *)"END\n");
}

void Kitchen::run()
{
    char *buffer;

    _inactiveThread = std::thread([this](){inactiveKitchen();});
    while ((buffer = *_ipc >> buffer) != NULL) {
        pointerFct(buffer);
        free(buffer);
    }
}
