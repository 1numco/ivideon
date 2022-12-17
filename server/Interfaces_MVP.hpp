#pragma once
#include <string>

template<class TEvent>
class EventNotifier
{
public:
    EventNotifier(): p_listener(nullptr) {}

    virtual ~EventNotifier(){}

    void setListener(TEvent * listener)
    {
        p_listener = listener;
    }

    void unsetListener()
    {
        p_listener = nullptr;
    }

    template<class T>
    void notify(void (TEvent::*pFn)(T&, T&), T& P1, T& P2)
    {
        if (p_listener)
            (p_listener->*pFn)(P1, P2);
    }
    
private:
    TEvent * p_listener;
};

class IViewEvent
{
public:
    virtual void handle_command(std::string& command, std::string& status) = 0;
    virtual ~IViewEvent(){}
};


class IView: public EventNotifier<IViewEvent>
{
public:
    virtual void print(std::string&& str) = 0;
    virtual void send_command(std::string& command, std::string& status) = 0;
    virtual ~IView(){}
};