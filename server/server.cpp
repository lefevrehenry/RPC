#include "server.h"

// Standard Library
#include <iostream>

using namespace rpc::server;

int Server::fibonacci(int n)
{
    if(n <= 1)
        return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

void Server::say_hello()
{
    std::cout << "Hello !" << std::endl;
}
