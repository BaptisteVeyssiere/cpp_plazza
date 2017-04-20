//
// Created by ilyas on 17/04/17.
//

#ifndef PLAZZA_THREAD_HPP
#define PLAZZA_THREAD_HPP

#include <memory>
#include <thread>

class Thread {

private:

    std::unique_ptr<std::thread>    thread;

public:

    Thread(std::shared_ptr<t_data> data);

    ~Thread();

    void join();
    bool joinable() const noexcept;

    void detach();

    void mainLoop(std::shared_ptr<t_data> data);

};



#endif //PLAZZA_THREAD_HPP
