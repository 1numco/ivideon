#pragma once

#include "Client_command.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>

class Client_command_factory
{
public:
    Client_command_factory() = default;
    Client_command_factory(Client_command_factory& other) = default;
    Client_command_factory(Client_command_factory&& other) = default;
    Client_command_factory& operator=(Client_command_factory& other) = default;
    Client_command_factory& operator=(Client_command_factory&& other) = default;
    ~Client_command_factory(){}
    std::unique_ptr<Client_command> create_command(std::string& command)
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
                return std::make_unique<Get_led_state>();
            if (command == "get-led-color")
                return std::make_unique<Get_led_color>();
            if (command == "get-led-rate")
                return std::make_unique<Get_led_rate>();
            else
            {
                throw std::runtime_error("Wrong command");
            }
        }
        if (part1 == "set-led-state")
            return std::make_unique<Set_led_state>(part2);
        if (part1 == "set-led-color")
            return std::make_unique<Set_led_color>(part2);
        if (part1 == "set-led-rate")
        {
            int rate = std::stoi(part2);
            return std::make_unique<Set_led_rate>(rate);
        }
        else
        {
            throw std::runtime_error("Wrong command");
        }
        

    }
};

class User_command_handler
{
public:
    User_command_handler()
    {
        factory = std::make_unique<Client_command_factory>();
    }
    User_command_handler(User_command_handler& other) = default;
    User_command_handler(User_command_handler&& other) = default;
    User_command_handler& operator=(User_command_handler& other) = default;
    User_command_handler& operator=(User_command_handler&& other) = default;
    ~User_command_handler(){}
    void handle(std::string& desc)
    {

        try
        {
            auto command = factory->create_command(desc);
            command->execute();
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
        

    }
private:
    std::unique_ptr<Client_command_factory> factory;
};

class User_command_receiver
{
public:
    User_command_receiver()
    {
        handler = std::make_unique<User_command_handler>();
    }
    User_command_receiver(User_command_receiver& other) = default;
    User_command_receiver(User_command_receiver&& other) = default;
    User_command_receiver& operator=(User_command_receiver& other) = default;
    User_command_receiver& operator=(User_command_receiver&& other) = default;
    ~User_command_receiver(){}
    void receive_commands()
    {      
        std::string line;
        while (std::getline(std::cin, line)) 
        {
            if (line == "exit")
                return;
            handler->handle(line);
            usleep(5);
        }
    }
private:
    std::unique_ptr<User_command_handler> handler;
};