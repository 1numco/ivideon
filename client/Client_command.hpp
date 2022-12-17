#pragma once
#include "ICommand.hpp"
#include <string>
#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;
class Client_command: public ICommand
{
public:
    Client_command() = default;
    Client_command(Client_command& other) = default;
    Client_command(Client_command&& other) = default;
    Client_command& operator=(Client_command& other) = default;
    Client_command& operator=(Client_command&& other) = default;
    virtual ~Client_command(){}
    virtual std::string to_string() = 0;
    virtual void execute() override
    {
        try 
        {
            asio::io_context io_context;

            asio::ip::tcp::endpoint ep(
                asio::ip::address::from_string(
                    "127.0.0.1"
                ),
                9999
            );
            asio::ip::tcp::socket sock(io_context);

            try
            {
                sock.connect(ep);
            }
            catch(const boost::system::system_error& ex)
            {
                std::cout << "Can't connect to server" << '\n';
                return;
            }

            std::string command = to_string() + "\n";

            try
            {
                asio::write(sock, asio::buffer(command.data(), strlen(command.data())));
            }
            catch(const boost::system::system_error& ex)
            {
                std::cout << "Can't send command to server" << '\n';
                return;
            }
            asio::streambuf b;
            try
            {
                asio::read_until(sock, b, "\n");
            }
            catch(const boost::system::system_error& ex)
            {
                std::cout << "Can't receive command from server" << '\n';
                return;
            }
            std::istream is(&b);
            std::string line;
            std::getline(is, line);
            std::cout << "Server response: " << line << std::endl;
        }
        catch(const boost::system::system_error& ex) {
            std::cout << "boost exception! " << ex.what() << std::endl;
        }
        catch(const std::exception& ex) {
            std::cout << "std::exception! " << ex.what() << std::endl;
        }
    }
};

class Set_led_state final: public Client_command
{
public:
    Set_led_state() = default;
    Set_led_state(std::string state): _state(state){}
    Set_led_state(Set_led_state& other) = default;
    Set_led_state(Set_led_state&& other) = default;
    Set_led_state& operator=(Set_led_state& other) = default;
    Set_led_state& operator=(Set_led_state&& other) = default;
    ~Set_led_state(){}
    std::string to_string() override
    {
        return std::string("set-led-state") + " " + _state + "\n";
    }
private:
    std::string _state;
};

class Set_led_color final: public Client_command
{
public:
    Set_led_color() = default;
    Set_led_color(std::string color): _color(color){}
    Set_led_color(Set_led_color& other) = default;
    Set_led_color(Set_led_color&& other) = default;
    Set_led_color& operator=(Set_led_color& other) = default;
    Set_led_color& operator=(Set_led_color&& other) = default;
    ~Set_led_color(){}
    std::string to_string() override
    {
        return std::string("set-led-color") + " " + _color + "\n";
    }
private:
    std::string _color;
};

class Set_led_rate final: public Client_command
{
public:
    Set_led_rate() = default;
    Set_led_rate(int rate): _rate(rate){}
    Set_led_rate(Set_led_rate& other) = default;
    Set_led_rate(Set_led_rate&& other) = default;
    Set_led_rate& operator=(Set_led_rate& other) = default;
    Set_led_rate& operator=(Set_led_rate&& other) = default;
    ~Set_led_rate(){}
    std::string to_string() override
    {
        return std::string("set-led-rate") + " " + std::to_string(_rate) + "\n";
    }
private:
    int _rate;
};

class Get_led_state final: public Client_command
{
public:
    Get_led_state() = default;
    Get_led_state(Get_led_state& other) = default;
    Get_led_state(Get_led_state&& other) = default;
    Get_led_state& operator=(Get_led_state& other) = default;
    Get_led_state& operator=(Get_led_state&& other) = default;
    ~Get_led_state(){}
    std::string to_string() override
    {
        return std::string("get-led-state") + "\n";
    }
};

class Get_led_color final: public Client_command
{
public:
    Get_led_color() = default;
    Get_led_color(Get_led_color& other) = default;
    Get_led_color(Get_led_color&& other) = default;
    Get_led_color& operator=(Get_led_color& other) = default;
    Get_led_color& operator=(Get_led_color&& other) = default;
    ~Get_led_color(){}
    std::string to_string() override
    {
        return std::string("get-led-color") + "\n";
    }
};

class Get_led_rate final: public Client_command
{
public:
    Get_led_rate() = default;
    Get_led_rate(Get_led_rate& other) = default;
    Get_led_rate(Get_led_rate&& other) = default;
    Get_led_rate& operator=(Get_led_rate& other) = default;
    Get_led_rate& operator=(Get_led_rate&& other) = default;
    ~Get_led_rate(){}
    std::string to_string() override
    {
        return std::string("get-led-rate") + "\n";
    }
};
