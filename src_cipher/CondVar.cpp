//
// Created by ilyas on 28/04/17.
//

#include "CondVar.hpp"


CondVar::CondVar(Mutex & mut) : lck(mut.getMutex()), cond() {

}

CondVar::~CondVar() {

}

void CondVar::lock() {
  lck.lock();
}

bool CondVar::try_lock() {
  return lck.try_lock();
}

void CondVar::unlock() {
  lck.unlock();
}

void CondVar::wait() {
  cond.wait(lck);
}

void CondVar::notify_one() noexcept {
  cond.notify_one();
}

void CondVar::notify_all() noexcept {
  cond.notify_all();
}
