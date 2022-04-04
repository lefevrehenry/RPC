#ifndef COMMON_COMMANDS_H
#define COMMON_COMMANDS_H

// Msgpack
#include <msgpack.hpp>

// ZMQPP
#include <zmqpp/zmqpp.hpp>

// Standard Library
#include <string>

namespace rpc
{

namespace command
{

using CommandId = unsigned int;
using Buffer = std::string;

template< typename T >
Buffer Serialize(const T& object)
{
    std::stringstream sbuf;
    msgpack::pack(sbuf, object);

    return sbuf.str();
}

template< typename T >
T Deserialize(const Buffer& buffer)
{
    T object;

    msgpack::object_handle oh = msgpack::unpack(buffer.data(), buffer.size());
    msgpack::object deserialized = oh.get();

    deserialized.convert(object);

    return object;
}

struct CommandWrapper {
   CommandId id;
   Buffer buffer;
};

class Command
{
    static CommandId N;

public:
    template< typename T>
    static CommandId Id()
    {
        static CommandId id = ++N;
        return id;
    }

    template< typename T >
    static std::string Name() {
        static std::string name = typeid(T).name();
        return name;
    }

    template< typename T >
    static CommandWrapper Wrap(const typename T::Request& object)
    {
        CommandId id = Id<T>();
        Buffer buffer = Serialize<typename T::Request>(object);

        return {id, buffer};
    }

    template< typename T >
    static CommandWrapper Wrap(const typename T::Reply& object)
    {
        CommandId id = Id<T>();
        Buffer buffer = Serialize<typename T::Reply>(object);

        return {id, buffer};
    }

    template< typename T >
    static typename T::Request UnwrapRequest(const CommandWrapper& command)
    {
        typename T::Request object = Deserialize<typename T::Request>(command.buffer);

        return object;
    }

    template< typename T >
    static typename T::Reply UnwrapReply(const CommandWrapper& command)
    {
        typename T::Reply object = Deserialize<typename T::Reply>(command.buffer);

        return object;
    }

    template< typename T, class ... Args >
    static CommandWrapper Create(Args&&... args)
    {
        T object = {std::forward<Args>(args)...};

        return Wrap<T>(object);
    }

    static zmqpp::message Pack(const CommandWrapper& command);

    static CommandWrapper Unpack(zmqpp::message& message);
};

struct EvaluateFibonacci
{
    struct Request {
        int n;
        MSGPACK_DEFINE(n);
    };

    struct Reply {
        int n;
        MSGPACK_DEFINE(n);
    };
};

struct SayHello
{
    struct Request {
        MSGPACK_DEFINE();
    };

    struct Reply {
        MSGPACK_DEFINE();
    };
};

};

};

#endif // COMMON_COMMANDS_H
