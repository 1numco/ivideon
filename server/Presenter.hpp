#pragma once
#include "Interfaces_MVP.hpp"
#include "Server_command_factory.hpp"
#include "Diod.hpp"
#include <memory>
#include <string>

class Presenter final: public IViewEvent
{
public:
    Presenter(std::shared_ptr<IView> view, std::shared_ptr<Diod> diod): _view(view), _diod(diod)
    {
        std::cout << _diod->to_string() << std::endl;
        factory = std::make_unique<Server_command_factory>(diod);
        _view->setListener(this);
    }

    ~Presenter()
    {
        _view->unsetListener();
    }

    void handle_command(std::string& command, std::string& status) override
    {
        try
        {
            auto com = factory->create_command(command);
            com->execute();
            status = com->status();
            _view->print(_diod->to_string());
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }

private:
    std::shared_ptr<IView> _view;
    std::shared_ptr<Diod> _diod;
    std::unique_ptr<Server_command_factory> factory;
};