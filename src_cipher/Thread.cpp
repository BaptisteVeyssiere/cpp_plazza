//
// Thread.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Sun Apr 30 04:10:36 2017 Baptiste Veyssiere
// Last update Sun Apr 30 19:13:56 2017 Baptiste Veyssiere
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include "Thread.hpp"
#include "Finder.hpp"

Thread::Thread(std::shared_ptr<t_data> data) : thread(new std::thread(&Thread::mainLoop, this, data)) {
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

void Thread::findSomething(std::vector<std::string> &data, std::vector<char> const& mem,
			   Information const& info)
{
  switch (info)
    {
    case Information::EMAIL_ADDRESS :
      Finder::findMailCiphered(data, mem);
      break;
    case Information::IP_ADDRESS :
      Finder::findIPCiphered(data, mem);
      break;
    case Information::PHONE_NUMBER :
      Finder::findPhoneCiphered(data, mem);
      break;
    default:
      break;
    }
}

std::vector<char> Thread::getFileData(std::string const& path)
{
    std::ifstream   file(path, std::ios::in | std::ios::ate);
    if (file.is_open()) {
        std::streampos size = file.tellg();
        if (!file.fail() && size > 0) {
            std::vector<char> fileMem(static_cast<unsigned long>(size) + 1);
            file.seekg(0, std::ios::beg);
            if (!file.fail()) {
                file.read(fileMem.data(), static_cast<std::streamsize>(size));
                if (!file.fail()) {
                    return (fileMem);
                }
            }
        }
        file.close();
    }
    std::cerr << "Something went wrong with the given file : " << path << std::endl;
    return (std::vector<char>());
}

void Thread::mainLoop(std::shared_ptr<t_data> data) {
    while (1) {
        while (!data->ready) {
	  std::this_thread::yield();
        }
        data->running = 1;
        data->ready = 0;
        std::vector<char> mem = getFileData(data->command.file);
        if (mem.size() > 1) {
	  std::vector<std::string> fileData;
	  findSomething(fileData, mem, data->command.information);
	  std::for_each(fileData.begin(), fileData.end(),
			[&](std::string &val) { std::replace(val.begin(), val.end(), ' ', ':'); });
	  data->command.data = fileData;
        }
	data->end = 1;
        data->running = 0;
    }
}
