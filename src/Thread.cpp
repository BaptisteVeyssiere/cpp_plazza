//
// Created by ilyas on 17/04/17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include "Thread.hpp"

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

void Thread::findMail(std::vector<std::string> &data, std::string const &mem) {
    std::regex  reg("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");
    std::smatch mail;
    std::string content = mem;

    while (std::regex_search(content, mail, reg)) {
        data.push_back(mail.str());
        content = mail.suffix().str();
    }
}

void Thread::findIP(std::vector<std::string> &data, std::string const &mem) {
    std::regex  reg("([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])");
    std::smatch ip;
    std::string content = mem;

    while (std::regex_search(content, ip, reg)) {
        data.push_back(ip.str());
        content = ip.suffix().str();
    }
}

void Thread::findPhone(std::vector<std::string> &data, std::string const &mem) {
    std::regex  reg("([0-9]|[0-9] ){10}");
    std::smatch phone;
    std::string content = mem;

    while (std::regex_search(content, phone, reg)) {
        data.push_back(phone.str());
        content = phone.suffix().str();
    }
}

void Thread::findSomething(std::vector<std::string> &data, std::string const& mem, Information const& info) {
    switch (info) {
        case Information::EMAIL_ADDRESS :
            findMail(data, mem);
            break;
        case Information::IP_ADDRESS :
            findIP(data, mem);
            break;
        case Information::PHONE_NUMBER :
            findPhone(data, mem);
            break;
        default:
            break;
    }
}

std::string Thread::getFileData(std::string const& path)
{
    std::ifstream   file(path, std::ios::in | std::ios::ate);
    if (file.is_open()) {
        std::streampos size = file.tellg();
        if (!file.fail() && size > 0) {
            std::vector<char> fileMem(static_cast<unsigned long>(size));
            file.seekg(0, std::ios::beg);
            if (!file.fail()) {
                file.read(fileMem.data(), static_cast<std::streamsize>(size));
                if (!file.fail()) {
                    return (std::string(fileMem.data()));
                }
            }
        }
        file.close();
    }
    std::cerr << "Something went wrong with the given file : " << path << std::endl;
    return (std::string(""));
}

void Thread::mainLoop(std::shared_ptr<t_data> data) {
    while (1) {
        while (!data->ready) {
            std::this_thread::yield();
        }
        data->running = 1;
        data->ready = 0;
        std::string mem = getFileData(data->command.file);
        if (mem != "") {
            std::vector<std::string> fileData;
            findSomething(fileData, mem, data->command.information);
            std::for_each(fileData.begin(), fileData.end(),
                          [&](std::string &val) { std::cout << val << std::endl; });
        }
        data->running = 0;
    }
}
