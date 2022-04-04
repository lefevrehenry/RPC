#include <client/client.h>
#include <common/commands.h>

using namespace rpc::client;
using namespace rpc::command;

int main()
{
    Client client;

    {
        typename SayHello::Reply reply;
        reply = client.execute<SayHello>();
    }

    {
        typename EvaluateFibonacci::Reply reply;

        reply = client.execute<EvaluateFibonacci>(6);
        std::cout << reply.n << std::endl;

        reply = client.execute<EvaluateFibonacci>(8);
        std::cout << reply.n << std::endl;
    }

    return 0;
}
