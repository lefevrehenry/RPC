#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include <any>
#include <mutex>
#include <thread>
#include <stdlib.h>
#include <sstream>
#include <future>

// using Real = double;
//
// struct ComputeFactorial
// {
//     struct Request {
//         int n;
//     };
//
//     struct Reply {
//         int value;
//     };
// };
//
// // y = (a * x) + b
// struct EvaluateMonome
// {
//     struct Request {
//         Real a;
//         Real b;
//         Real x;
//     };
//
//     struct Reply {
//         Real y
//     };
// };
//
// // blocking operation
// // non-blocking operation

#include <server/server.h>
#include <server/server_stub.h>
#include <server/server_runtime.h>

int main()
{
    std::cout << "hello" << std::endl;

    rpc::server::ServerInfo server_info;
    server_info.binding_point = "tcp://*:4242";

    rpc::server::ServerRuntime server_runtime(server_info);

    return server_runtime.exec();
}
