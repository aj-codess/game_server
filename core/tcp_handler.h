#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <login_routes.h>
#include <auth_check.h>

using namespace std;

class tcp_handler{
    private:
    auth auth_handler;
    login_routes login_handler;

    public:
    tcp_handler()=default;
    void processor(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res, boost::beast::tcp_stream& stream_socket ,std::function<void()> callback);
};



void tcp_handler::processor(boost::beast::http::request<boost::beast::http::string_body>& req,boost::beast::http::response<boost::beast::http::string_body>& res, boost::beast::tcp_stream& stream_socket,std::function<void()> callback){



}