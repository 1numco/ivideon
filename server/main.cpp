#include "View.hpp"
#include "Presenter.hpp"
#include "Diod.hpp"
#include "Server.hpp"
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <iostream>

int main()
{
    auto view = std::make_shared<View>();
    Presenter presenter(view, std::make_unique<Diod>());
    try
    {
        boost::asio::io_context io_context;

        Server server(io_context, 9999, view);

        io_context.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << "\n";
    }
    return 0;
}