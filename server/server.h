#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

namespace rpc
{

namespace server
{

struct Server
{
    int fibonacci(int n);

    void say_hello();
};

};

};

#endif // SERVER_SERVER_H
