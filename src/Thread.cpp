//
// Created by ilyas on 17/04/17.
//

#include "Thread.hpp"

Thread::Thread(std::shared_ptr<t_data> data) {
    std::unique_ptr<std::thread> th(new std::thread(&Thread::mainLoop, this, data));
    thread.swap(th);
}

Thread::~Thread() {

}

void Thread::join() {
    thread->join();
}

bool Thread::joinable() const noexcept {
    return thread->joinable();
}

void Thread::detach() {
    thread->detach();
}

void Thread::mainLoop(std::shared_ptr<t_data> data) {
    while (1) {
        std::this_thread::yield();
    }
}
