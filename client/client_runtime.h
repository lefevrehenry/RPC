#ifndef CLIENT_CLIENT_RUNTIME_H
#define CLIENT_CLIENT_RUNTIME_H

// RPC
#include <common/commands.h>

// ZMQPP
#include <zmqpp/zmqpp.hpp>

namespace rpc
{

namespace client
{

struct ClientInfo
{
    std::string binding_point;
};

class ClientRuntime
{

public:
    ClientRuntime(const ClientInfo& client_info);
    ~ClientRuntime();

public:
    command::CommandWrapper send(const command::CommandWrapper& request_command);

private:
    zmqpp::context m_zmq_context;
    zmqpp::socket m_socket;

    ClientInfo m_client_info;

};

};

};

#endif // CLIENT_CLIENT_RUNTIME_H
