//
// Created by ilyas on 17/04/17.
//

#ifndef PLAZZA_THREAD_HPP
#define PLAZZA_THREAD_HPP

#include <memory>
#include <thread>

class Thread {

private:

    std::shared_ptr<std::thread>    thread;

public:

    template <class Fn, class... Args>
    Thread(Fn &&fn, Args&&... args) {
        thread = std::make_shared<std::thread>(fn, args...);
    }

    ~Thread();

    void join();
    bool joinable() const noexcept;

    void detach();

};


#endif //PLAZZA_THREAD_HPP
