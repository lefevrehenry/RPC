#include "server_stub.h"

using namespace rpc::command;
using namespace rpc::server;

Stub::Stub() :
    m_server(),
    m_commandsMapping()
{
    registerCommand<EvaluateFibonacci>();
    registerCommand<SayHello>();
}

zmqpp::message Stub::unpack(zmqpp::message& input_message) {
    CommandWrapper input_command = Command::Unpack(input_message);

    CommandId id = input_command.id;

    if(id > m_commandsMapping.size()) {
        throw std::runtime_error("ServerStub receives an unknown CommandId '" + std::to_string(id) + "'");
    }

    const Executor& executor = m_commandsMapping.at(id);

    if(!executor) {
        throw std::runtime_error("Not executor registered for CommandId '" + std::to_string(id) + "'");
    }

    CommandWrapper output_command = executor(input_command);

    zmqpp::message output_message = Command::Pack(output_command);

    return output_message;
}

template< typename T >
void Stub::registerCommand()
{
    CommandId id = Command::Id<T>();

    if(m_commandsMapping.count(id) != 0) {
        throw std::runtime_error("Command '" + Command::Name<T>() + "' already registered");
    }

    Executor executor = std::bind(&Stub::unwrapCommand<T>, this, std::placeholders::_1);

    m_commandsMapping[id] = executor;
}

template< typename T >
CommandWrapper Stub::unwrapCommand(const CommandWrapper& input_command)
{
    typename T::Request object = Command::UnwrapRequest<T>(input_command);

    const typename T::Reply& reply = execute<T>(object);

    CommandWrapper output_command = Command::Wrap<T>(reply);

    return output_command;
}

template<>
EvaluateFibonacci::Reply Stub::execute<EvaluateFibonacci>(const EvaluateFibonacci::Request& parameters)
{
    int n = m_server.fibonacci(parameters.n);

    return {n};
}

template<>
SayHello::Reply Stub::execute<SayHello>(const SayHello::Request& parameters)
{
    m_server.say_hello();

    return {};
}
