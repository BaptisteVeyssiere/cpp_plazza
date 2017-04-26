//
// Created by ilyas on 18/04/17.
//

#include "Mutex.hpp"


Mutex::Mutex()
  : mutex(std::make_shared<std::mutex>())
{}

Mutex::~Mutex() {
}

void Mutex::lock() {
    mutex->lock();
}

bool Mutex::try_lock() {
    return mutex->try_lock();
}

void Mutex::unlock() {
    mutex->unlock();
}
