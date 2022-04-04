#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

// RPC
#include <client/client_stub.h>

namespace rpc
{

namespace client
{

class Client
{

public:
    Client();

public:
    template< typename T, class ... Args >
    typename T::Reply execute(Args&&... args)
    {
        typename T::Request object = {std::forward<Args>(args)...};

        typename T::Reply reply = m_stub.pack<T>(object);

        return reply;
    };

private:
    Stub m_stub;

};

};

};

#endif // CLIENT_CLIENT_H
