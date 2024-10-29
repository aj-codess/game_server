#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <global_dcl.h>

using namespace std;

class server_handler{
    public:
    server_handler(boost::asio::io_context& context,domain_dcl init)
    :ioc(context),addr_resolver(context),domain(init) {

        cout<<"Server Initialised"<<endl;

    };

    private:
    domain_dcl domain;
    boost::asio::io_context& ioc;
    boost::asio::ip::tcp::resolver addr_resolver;
};