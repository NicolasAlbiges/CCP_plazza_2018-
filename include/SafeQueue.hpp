/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** CCP_plazza_2018/include/SafeQueue.hpp
*/

#ifndef _SAFE_QUEUE_HPP_
#define _SAFE_QUEUE_HPP_

#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>
#include "IPizza.hpp"

template<typename T>
class SafeQueue
{
    public:
        SafeQueue() {
            _empty = true;
            _cooking = 0;
            _time = std::chrono::system_clock::now();
        };
        ~SafeQueue() {};

        void push(T val) {
            std::unique_lock<std::mutex> lock(_mut);

            _queue.push(val);
            _empty = false;
            _cv.notify_one();
        }

        T pop() {
            T val;
            std::unique_lock<std::mutex> lock(_mut);

            _cv.wait(lock, [this]{return !_empty;});
            val = _queue.front();
            _queue.pop();
            _empty = _queue.empty();
            _cooking += 1;
            return val;
        }

        void finishCook(Pizza_t pizza) {
            std::unique_lock<std::mutex> lock(_mut);
            std::string type;
            std::string size;

            if (_cooking == 1 && _queue.size() == 0)
                _time = std::chrono::system_clock::now();
            switch (pizza.type) {
                case Regina:
                    type = "regina";
                    break;
                case Margarita:
                    type = "margarita";
                    break;
                case Americana:
                    type = "americana";
                    break;
                default:
                    type = "fantasia";
                    break;
            }
            switch (pizza.size) {
                case S:
                    size = "S";
                    break;
                case L:
                    size = "L";
                    break;
                case XL:
                    size = "XL";
                    break;
                default:
                    size = "XXL";
                    break;
            }
            printf("Finish Pizza : %s %s !\n", type.c_str(), size.c_str());
            _cooking -= 1;
        }

        int getQueueSize() {
            std::unique_lock<std::mutex> lock(_mut);

            return _queue.size();
        }

        int getCooking() {
            std::unique_lock<std::mutex> lock(_mut);

            return _cooking;
        }

        std::chrono::system_clock::time_point getInactive() {
            std::unique_lock<std::mutex> lock(_mut);

            return _time;
        }

    private:
        std::chrono::system_clock::time_point _time;
        std::condition_variable _cv;
        std::queue<T> _queue;
        std::mutex _mut;
        int _cooking;
        bool _empty;
};

#endif