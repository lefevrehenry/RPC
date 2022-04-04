#ifndef CLIENT_CLIENT_STUB_H
#define CLIENT_CLIENT_STUB_H

// RPC
#include <client/client_runtime.h>
#include <common/commands.h>

namespace rpc
{

namespace client
{

struct Stub
{

public:
    Stub();

public:
    template< typename T >
    typename T::Reply pack(const typename T::Request& object)
     {
         command::CommandWrapper request_command = command::Command::Wrap<T>(object);

         command::CommandWrapper reply_command = m_client_runtime.send(request_command);

         typename T::Reply reply = command::Command::UnwrapReply<T>(reply_command);

         return reply;
     }

private:
    ClientRuntime m_client_runtime;

};

};

};
#endif // CLIENT_CLIENT_STUB_H
