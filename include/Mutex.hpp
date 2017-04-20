//
// Created by ilyas on 18/04/17.
//

#ifndef PLAZZA_MUTEX_HPP
#define PLAZZA_MUTEX_HPP

#include <mutex>
#include <memory>

class Mutex {

private:

    std::shared_ptr<std::mutex>    mutex;

public:

    Mutex();
    ~Mutex();

    void    lock();
    bool    try_lock();
    void    unlock();

};


#endif //PLAZZA_MUTEX_HPP
