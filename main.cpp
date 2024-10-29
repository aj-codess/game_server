#include <iostream>
#include <string>

#include <boost/asio.hpp>


#include <global_dcl.h>
#include <server_handler.h>

using namespace std;

int main(){

    boost::asio::io_context context;

    domain_dcl domain={
        "localhost",
        "5000"
    };

    server_handler server;

    server(context,domain);

    return 0;
}