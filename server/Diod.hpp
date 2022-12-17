#pragma once

#include <string>
#include <stdexcept>
#include <set>

class Diod
{
public:

    Diod(bool state = false, std::string color = "red", int rate = 0): _state(state), 
                                                                       _color(color),
                                                                       _rate(rate)
    {
        __initiazile_availables();
    }

    Diod(Diod& other) = default;
    Diod(Diod&& other) = default;
    Diod& operator= (Diod& other) = default;
    Diod& operator= (Diod&& other)  = default;
    ~Diod(){}

    void set_state(std::string state)
    {
        if (_available_states.count(state))
        {
            _state = ("on" == state);
        }
        else
            throw std::runtime_error("Wrong state");  
    }

    void set_color(std::string color)
    {
        if (_available_colors.count(color))
        {
            _color = color;
        }
        else
            throw std::runtime_error("Wrong color");  
    }

    void set_rate(int rate)
    {
        if (_available_rates.count(rate))
        {
            _rate = rate;
        }
        else
            throw std::runtime_error("Wrong rate"); 
    }

    std::string get_state()
    {
        return _state ? "on" : "off";
    }

    std::string get_color()
    {
        return _color;
    }

    int get_rate()
    {
        return _rate;
    }

    std::string to_string()
    {
        return std::string("state is ") + 
               (_state ? "on" : "off") + 
               std::string(", color is ") +
               _color +
               std::string(", rate is ") +
               std::to_string(_rate);
    }
private:
    void __initiazile_availables()
    {
        _available_states = {"on", "off"};
        _available_colors = {"red", "green", "blue"};
        _available_rates = {0, 1, 2, 3, 4, 5};
    }
    bool _state;
    std::string _color;
    int _rate;
    std::set<std::string> _available_states;
    std::set<std::string> _available_colors;
    std::set<int> _available_rates;
};