#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include "Interfaces_MVP.hpp"
#include <boost/asio.hpp>
#include <mutex>

using boost::asio::ip::tcp;
namespace asio = boost::asio;

class Session: public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, std::shared_ptr<IView> view): socket_(std::move(socket)), view_(view) {}

    void start()
    {
        do_read();
    }

private:
    void do_read()
    {
        auto self(shared_from_this());
        asio::async_read_until(socket_, asio::dynamic_buffer(data), '\n',
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::string status;
                data = data.substr(0, data.length() - 2);
                m.lock();
                view_->send_command(data, status);
                m.unlock();
                status += "\n";
                data = status;
                do_write(data.length());
            }
            else
            {
                asio::async_write(socket_, asio::buffer("Failed to receive command", 25),
                    [this, self](boost::system::error_code ec, std::size_t /*length*/)
                    {
                        if (ec)
                        {
                            std::lock_guard lock(m);
                            std::cout << "Connection problems" << std::endl;
                        }
                    });
            }
        });
    
  }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this());
        asio::async_write(socket_, asio::buffer(data.data(), length),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
            {
                if (ec)
                {
                    std::lock_guard lock(m);
                    std::cout << "Connection problems" << std::endl;
                }
            });
    }

private:
    tcp::socket socket_;
    std::shared_ptr<IView> view_;
    std::string data;
    std::mutex m;
};

class Server
{
public:
    Server(asio::io_context& io_context, short port, std::shared_ptr<IView> view)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), view_(view)
    {
        do_accept();
    }

private:
    void do_accept()
    {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                std::make_shared<Session>(std::move(socket), view_)->start();
                }

                do_accept();
            });
    }

    tcp::acceptor acceptor_;
    std::shared_ptr<IView> view_;
};