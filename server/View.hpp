#pragma once
#include "Interfaces_MVP.hpp"
#include <string>
#include <iostream>

class View final: public IView
{
public:
    View() = default;
    View(View& other) = default;
    View(View&& other) = default;
    View& operator=(View& other) = default;
    View& operator=(View&& other) = default;
    ~View(){}
    void send_command(std::string& command, std::string& status) override
    {
        notify(&IViewEvent::handle_command, command, status);
    }
    void print(std::string&& str) override
    {
        std::cout << str << std::endl;
    }
};