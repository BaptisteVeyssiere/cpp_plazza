//
// Created by ilyas on 17/04/17.
//

#include "Thread.hpp"


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
