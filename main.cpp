#include <iostream>
#include <string>

#include <boost/asio.hpp>


#include <global_dcl.h>
#include <server_handler.h>

using namespace std;

class override{
    private:
    server_handler server;

    public:
    override(boost::asio::io_context& context,domain_dcl init)
    :server(context,init){

        cout<<"server handler called "<<endl;

    };
};


int main(){

    boost::asio::io_context context;

    domain_dcl domain={
        "localhost",
        "8080"
    };

    override server_init(context,domain);

    return 0;
};