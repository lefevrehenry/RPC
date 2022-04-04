#include "client_runtime.h"

using namespace rpc::client;
using namespace rpc::command;

ClientRuntime::ClientRuntime(const ClientInfo& client_info) :
    m_zmq_context(),
    m_socket(m_zmq_context, zmqpp::socket_type::pair),
    m_client_info(client_info)
{
    m_socket.connect(client_info.binding_point);
}

ClientRuntime::~ClientRuntime()
{
    m_socket.close();
}

CommandWrapper ClientRuntime::send(const CommandWrapper& request_command)
{
    zmqpp::message request_message = Command::Pack(request_command);
    m_socket.send(request_message);

    zmqpp::message reply_message;
    m_socket.receive(reply_message);

    CommandWrapper reply_command = Command::Unpack(reply_message);

    return reply_command;
}
