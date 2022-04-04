#include "server_runtime.h"

// Standard Library
#include <unistd.h>

using namespace rpc::server;

ServerRuntime::ServerRuntime(const ServerInfo& server_info) :
    m_zmq_context(),
    m_poller(),
    m_socket(m_zmq_context, zmqpp::socket_type::pair),
    m_server_info(server_info),
    m_stub()
{
    m_socket.bind(server_info.binding_point);

    m_poller.add(m_socket, zmqpp::poller::poll_in);
    m_poller.add(STDIN_FILENO, zmqpp::poller::poll_in);
}

ServerRuntime::~ServerRuntime()
{
    m_socket.close();
}

int ServerRuntime::exec()
{
    int exit_code = EXIT_SUCCESS;

    bool should_exit = false;

    while(!should_exit)
    {
        if(m_poller.poll(zmqpp::poller::wait_forever))
        {
            if(m_poller.has_input(m_socket))
            {
                zmqpp::message input_message;

                // receive the request message
                m_socket.receive(input_message);

                zmqpp::message output_message = m_stub.unpack(input_message);

                // send the reply message
                m_socket.send(output_message);
            }
            else if(m_poller.has_input(STDIN_FILENO))
            {
                std::string command;
                std::getline(std::cin, command);

                should_exit = true;
            }
        }
    }

    return exit_code;
}
