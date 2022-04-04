#ifndef SERVER_SERVER_RUNTIME_H
#define SERVER_SERVER_RUNTIME_H

// RPC
#include <server/server_stub.h>

// ZMQPP
#include <zmqpp/zmqpp.hpp>

// Standard Library
#include <string>

namespace rpc
{

namespace server
{

struct ServerInfo
{
    std::string binding_point;
};

class ServerRuntime
{

public:
    ServerRuntime(const ServerInfo& server_info);
    ~ServerRuntime();

public:
    int exec();

private:
    zmqpp::context m_zmq_context;
    zmqpp::poller m_poller;
    zmqpp::socket m_socket;

    ServerInfo m_server_info;
    Stub m_stub;

};

};

};

#endif // SERVER_SERVER_RUNTIME_H
