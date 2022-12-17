#pragma once

#include "Diod.hpp"
#include "Server_command.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>

class Server_command_factory
{
public:
    Server_command_factory() = delete;
    Server_command_factory(std::shared_ptr<Diod> diod): _diod(diod) {}
    Server_command_factory(Server_command_factory& other) = default;
    Server_command_factory(Server_command_factory&& other) = default;
    Server_command_factory& operator=(Server_command_factory& other) = default;
    Server_command_factory& operator=(Server_command_factory&& other) = default;
    ~Server_command_factory(){}

    std::unique_ptr<Server_command> create_command(std::string& command)
    {
        
        size_t pos = 0;
        std::string delimiter = " ";
        std::string part1;
        std::string part2;
        if ((pos = command.find(delimiter)) != std::string::npos)
        {
            part1 = command.substr(0, pos);
            part2 = command.substr(pos + delimiter.length(), std::string::npos);
        }
        else
        {
            if (command == "get-led-state")
                return std::make_unique<Get_led_state>(_diod);
            if (command == "get-led-color")
                return std::make_unique<Get_led_color>(_diod);
            if (command == "get-led-rate")
                return std::make_unique<Get_led_rate>(_diod);
            else
            {
                throw std::runtime_error("Wrong command");
            }
        }
        if (part1 == "set-led-state")
            return std::make_unique<Set_led_state>(_diod, part2);
        if (part1 == "set-led-color")
            return std::make_unique<Set_led_color>(_diod, part2);
        if (part1 == "set-led-rate")
        {
            int rate = std::stoi(part2);
            return std::make_unique<Set_led_rate>(_diod, rate);
        }
        else
        {
            throw std::runtime_error("Wrong command");
        }
        

    }
private:
    std::shared_ptr<Diod> _diod;
};