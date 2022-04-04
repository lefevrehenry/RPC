#include "commands.h"

using namespace rpc::command;

CommandId Command::N = 0;

namespace {
    CommandId a = Command::Id<EvaluateFibonacci>();
    CommandId b = Command::Id<SayHello>();
}

zmqpp::message Command::Pack(const CommandWrapper& command)
{
    zmqpp::message message;

    message << command.id;
    message << command.buffer;

    return message;
}

CommandWrapper Command::Unpack(zmqpp::message& message)
{
    CommandWrapper command;

    message >> command.id;
    message >> command.buffer;

    return command;
}
