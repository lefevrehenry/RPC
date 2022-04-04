#include "client_stub.h"

using namespace rpc::client;

static ClientInfo client_info = {"tcp://localhost:4242"};

Stub::Stub() :
    m_client_runtime(client_info)
{
}
