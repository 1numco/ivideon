#pragma once
#include "ICommand.hpp"
#include "Diod.hpp"
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;
class Server_command: public ICommand
{
public:
    Server_command() = default;
    Server_command(std::shared_ptr<Diod> diod): _diod(diod) {}
    Server_command(Server_command& other) = default;
    Server_command(Server_command&& other) = default;
    Server_command& operator=(Server_command& other) = default;
    Server_command& operator=(Server_command&& other) = default;
    virtual ~Server_command(){}
    virtual void execute() override {}
    virtual std::string status()
    {
        return _status;
    }
protected:
    std::shared_ptr<Diod> _diod;
    std::string _status;
};

class Set_led_state final: public Server_command
{
public:
    Set_led_state() = default;
    Set_led_state(std::shared_ptr<Diod> diod, std::string state): Server_command(diod), _state(state){}
    Set_led_state(Set_led_state& other) = default;
    Set_led_state(Set_led_state&& other) = default;
    Set_led_state& operator=(Set_led_state& other) = default;
    Set_led_state& operator=(Set_led_state&& other) = default;
    ~Set_led_state(){}
    void execute() override 
    {
        try
        {
           _diod->set_state(_state);
            _status = "OK";
        }
        catch(const std::exception& e)
        {
            _status = "FAILED";
        }
    }
private:
    std::string _state;
};

class Set_led_color final: public Server_command
{
public:
    Set_led_color() = default;
    Set_led_color(std::shared_ptr<Diod> diod, std::string color): Server_command(diod), _color(color){}
    Set_led_color(Set_led_color& other) = default;
    Set_led_color(Set_led_color&& other) = default;
    Set_led_color& operator=(Set_led_color& other) = default;
    Set_led_color& operator=(Set_led_color&& other) = default;
    ~Set_led_color(){}
    void execute() override 
    {
        try
        {
           _diod->set_color(_color);
            _status = "OK";
        }
        catch(const std::exception& e)
        {
            _status = "FAILED";
        }
    }
private:
    std::string _color;
};

class Set_led_rate final: public Server_command
{
public:
    Set_led_rate() = default;
    Set_led_rate(std::shared_ptr<Diod> diod, int rate): Server_command(diod), _rate(rate){}
    Set_led_rate(Set_led_rate& other) = default;
    Set_led_rate(Set_led_rate&& other) = default;
    Set_led_rate& operator=(Set_led_rate& other) = default;
    Set_led_rate& operator=(Set_led_rate&& other) = default;
    ~Set_led_rate(){}
    void execute() override 
    {
        try
        {
            _diod->set_rate(_rate);
            _status = "OK";
        }
        catch(const std::exception& e)
        {
            _status = "FAILED";
        }
    }
private:
    int _rate;
};

class Get_led_state final: public Server_command
{
public:
    Get_led_state() = default;
    Get_led_state(std::shared_ptr<Diod> diod): Server_command(diod){}
    Get_led_state(Get_led_state& other) = default;
    Get_led_state(Get_led_state&& other) = default;
    Get_led_state& operator=(Get_led_state& other) = default;
    Get_led_state& operator=(Get_led_state&& other) = default;
    ~Get_led_state(){}
    void execute() override
    {
        try
        {
            _status = "OK " + _diod->get_state();
        }
        catch(const std::exception& e)
        {
            _status = "FAILED";
        }
    }
};

class Get_led_color final: public Server_command
{
public:
    Get_led_color() = default;
    Get_led_color(std::shared_ptr<Diod> diod): Server_command(diod){}
    Get_led_color(Get_led_color& other) = default;
    Get_led_color(Get_led_color&& other) = default;
    Get_led_color& operator=(Get_led_color& other) = default;
    Get_led_color& operator=(Get_led_color&& other) = default;
    ~Get_led_color(){}
    void execute() override
    {
        try
        {
            _status = "OK " + _diod->get_color();
        }
        catch(const std::exception& e)
        {
            _status = "FAILED";
        }
    }
};

class Get_led_rate final: public Server_command
{
public:
    Get_led_rate() = default;
    Get_led_rate(std::shared_ptr<Diod> diod): Server_command(diod){}
    Get_led_rate(Get_led_rate& other) = default;
    Get_led_rate(Get_led_rate&& other) = default;
    Get_led_rate& operator=(Get_led_rate& other) = default;
    Get_led_rate& operator=(Get_led_rate&& other) = default;
    ~Get_led_rate(){}
    void execute() override
    {
        try
        {
            _status = "OK " + std::to_string(_diod->get_rate());
        }
        catch(const std::exception& e)
        {
            _status = "FAILED";
        }
    }
};
