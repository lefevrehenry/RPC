#ifndef SERVER_SERVER_STUB_H
#define SERVER_SERVER_STUB_H

// RPC
#include <server/server.h>
#include <common/commands.h>

// ZMQPP
#include <zmqpp/zmqpp.hpp>

// Standard Library
#include <functional>
#include <map>

namespace rpc
{

namespace server
{

struct Stub
{

public:
    Stub();

public:
    zmqpp::message unpack(zmqpp::message& input_message);

private:
    template< typename T >
    void registerCommand();

    template< typename T >
    command::CommandWrapper unwrapCommand(const command::CommandWrapper& input_command);

    template< typename T >
    typename T::Reply execute(const typename T::Request& parameters) {
        throw std::runtime_error("undefined executor for Command '" + command::Command::Name<T>() + "'");
    }

private:
    Server m_server;

    using Executor = std::function<command::CommandWrapper(command::CommandWrapper)>;
    std::map<command::CommandId, Executor> m_commandsMapping;

};

};

};
#endif // SERVER_SERVER_STUB_H
