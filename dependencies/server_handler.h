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

        this->endP_maker();

    };

    private:
    domain_dcl domain;
    boost::asio::io_context& ioc;
    boost::asio::ip::tcp::resolver addr_resolver;
    boost::asio::ip::tcp::endpoint endpoint;
    void endP_maker();
};


void server_handler::endP_maker(){

    try{

        boost::asio::ip::tcp::resolver::results_type resolved_endpoints=this->addr_resolver.async_resolve(this->domain.domain,this->domain.port,[&](boost::system::error_code& ec,boost::){

        });

    } catch(const std::exception& e){

        cout<<"Error with endpoint - "<<e.what()<<endl;

    };

};