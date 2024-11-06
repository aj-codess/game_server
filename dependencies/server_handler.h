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
    :ioc(context),addr_resolver(context),domain(init),connection_acceptor(context) {

        cout<<"Server Initialised"<<endl;

        this->endP_maker();

    };
    bool isRunning;

    private:
    short cycle_limit=10;
    short endp_cycle;
    domain_dcl domain;
    boost::asio::io_context& ioc;
    boost::asio::ip::tcp::acceptor connection_acceptor;
    boost::asio::ip::tcp::resolver addr_resolver;
    boost::asio::ip::tcp::endpoint endpoint;
    void endP_maker();
    void acceptor_init();
    void listener_init();
    void commu_handler_init(std::shared_ptr<boost::asio::ip::tcp::socket> socket,boost::asio::yield_context yield);
};


void server_handler::endP_maker(){

    try{

        boost::asio::ip::tcp::resolver::results_type resolved_endpoints=addr_resolver.resolve(this->domain.domain,this->domain.port);

        this->endpoint=*resolved_endpoints.begin();

        this->acceptor_init();



    } catch(const std::exception& e){

        cout<<"Error with endpoint - "<<e.what()<<endl;

    };

};



void server_handler::acceptor_init(){

    try{

        this->connection_acceptor.open(this->endpoint.protocol());

        this->connection_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));

        this->connection_acceptor.bind(this->endpoint);

        this->endp_cycle=0;

        this->connection_acceptor.listen();

    } catch(const std::exception& e){

        cout<<"error With acceptor - "<<e.what()<<endl;

        if(this->endp_cycle < this->cycle_limit){

            this->endp_cycle+=1;

            this->endP_maker();

        };

    };

};




void server_handler::listener_init(){

    auto socket=std::make_shared<boost::asio::ip::tcp::socket>(ioc);

    this->connection_acceptor.async_accept(*socket,[&](boost::system::error_code ec){

        if(!ec){

            this->isrunning=true;

            if(socket->is_open()){

                cout<<"client connection Acknoledged with ip - "<<socket->remote_endpoint()<<endl;

                boost::asio::spawn(connection_acceptor.get_executor(),[&](boost::asio::yield_context yield) {
        
                    this->commu_handler(socket, yield);

                });

            };

        } else{

            cout<<"Error Accepting - "<<ec.message()<<endl;

            this->listener_init();

        };

    });

};



void server_handler::commu_handler_init(std::shared_ptr<boost::asio::ip::tcp::socket> socket,boost::asio::yield_context yield){

    

};