/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** include/Ingredients.hpp
*/

#ifndef _INGREDIENTS_HPP_
#define _INGREDIENTS_HPP_

#include <thread>
#include <mutex>
#include <condition_variable>
#include "IPizza.hpp"

class Ingredients
{
    public:
        Ingredients(int stock) {
            _tomato = 5;
            _gruyere = 5;
            _ham = 5;
            _mushroom = 5;
            _steak = 5;
            _eggplant = 5;
            _goatCheese = 5;
            _chiefLove = 5;
            _stop = false;
            _t = std::thread([this, stock](){restock(stock);});
        };

        ~Ingredients() {};

        void restock(int stockTime) {
            std::unique_lock<std::mutex> lock(_mut, std::defer_lock);
            std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

            while (_stop == false) {
                if (std::chrono::duration<double, std::milli>(std::chrono::system_clock::now() - start).count() > stockTime) {
                    lock.lock();
                    start = std::chrono::system_clock::now();
                    _tomato += 1;
                    _gruyere += 1;
                    _ham += 1;
                    _mushroom += 1;
                    _steak += 1;
                    _eggplant += 1;
                    _goatCheese += 1;
                    _chiefLove += 1;
                    lock.unlock();
                    _cv.notify_one();
                    printf("Reload Stock!\n");
                }
            }
        }

        bool receipeMargarita() {
            if (_tomato >= 1 && _gruyere >= 1) {
                _tomato -= 1;
                _gruyere -= 1;
                return true;
            }
            return false;
        }

        bool receipeRegina() {
            if (_tomato >= 1 && _gruyere >= 1 && _ham >= 1) {
                _tomato -= 1;
                _gruyere -= 1;
                _ham -= 1;
                return true;
            }
            return false;
        }

        bool receipeAmericana() {
            if (_tomato >= 1 && _gruyere >= 1 && _steak >= 1) {
                _tomato -= 1;
                _gruyere -= 1;
                _steak -= 1;
                return true;
            }
            return false;
        }

        bool receipeFantasia() {
            if (_tomato >= 1 && _eggplant >= 1 && _goatCheese >= 1 && _chiefLove >= 1) {
                _tomato -= 1;
                _eggplant -= 1;
                _goatCheese -= 1;
                _chiefLove -= 1;
                return true;
            }
            return false;
        }

        bool doPizza(Pizza_t pizza) {
            std::unique_lock<std::mutex> lock(_mut);

            if (pizza.type == Margarita)
                return receipeMargarita();
            else if (pizza.type == Regina)
                return receipeRegina();
            else if (pizza.type == Americana)
                return receipeAmericana();
            else if (pizza.type == Fantasia)
                return receipeFantasia();
            return false;
        }

        std::string getIngredientList() {
            std::unique_lock<std::mutex> lock(_mut);

            return std::to_string(_tomato) + " " + std::to_string(_gruyere) + " " + std::to_string(_ham) + " " + std::to_string(_mushroom) + " " +
            std::to_string(_steak) + " " + std::to_string(_eggplant) + " " + std::to_string(_goatCheese) + " " + std::to_string(_chiefLove) + " ";
        }

        void Stop() {
            std::unique_lock<std::mutex> lock(_mut);

            _stop = true;
        }

        std::thread _t;

    private:
        int _tomato;
        int _gruyere;
        int _ham;
        int _mushroom;
        int _steak;
        int _eggplant;
        int _goatCheese;
        int _chiefLove;
        bool _stop;
        std::mutex _mut;
        std::condition_variable _cv;
};

#endif