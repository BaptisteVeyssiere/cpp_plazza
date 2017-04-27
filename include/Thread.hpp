//
// Created by ilyas on 17/04/17.
//

#ifndef PLAZZA_THREAD_HPP
#define PLAZZA_THREAD_HPP

#include <memory>
#include <thread>
#include <vector>
#include "data.hpp"

class Thread {

private:

    std::unique_ptr<std::thread>    thread;

public:

    Thread(std::shared_ptr<t_data> data);

    ~Thread();

    void join();
    bool joinable() const noexcept;

    void detach();

    void findMail(std::vector<std::string> &data, std::string const& mem);
    void findIP(std::vector<std::string> &data, std::string const& mem);
    void findPhone(std::vector<std::string> &data, std::string const& mem);
    void findSomething(std::vector<std::string> &data, std::string const& mem, Information const& info);

    void mainLoop(std::shared_ptr<t_data> data);

};



#endif //PLAZZA_THREAD_HPP
