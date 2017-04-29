//
// Created by ilyas on 28/04/17.
//

#ifndef PLAZZA_CONDVAR_HPP
#define PLAZZA_CONDVAR_HPP


#include <mutex>
#include <condition_variable>
#include "Mutex.hpp"

class CondVar {

private:

  std::unique_lock<std::mutex>  lck;
  std::condition_variable       cond;
  bool                          ready;

public:

  CondVar(Mutex &mut, bool &_ready);
  ~CondVar();

  void lock();

  bool try_lock();

  void unlock();

  void wait();

  void notify_one() noexcept ;
  void notify_all() noexcept ;

private:

  CondVar();

};


#endif //PLAZZA_CONDVAR_HPP
