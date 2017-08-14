#ifndef GLIAD_SERVER_H
#define GLIAD_SERVER_H

#include <grpc++/grpc++.h>
#include "server.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using glia::common::proto::Request;
using glia::common::proto::Reply;

namespace glia {
    namespace gliad {
        namespace services {
            class Server final : public glia::common::proto::Server::Service {
                Status gossip(
                    ServerContext *context,
                    const Request *request,
                    Reply *reply
                ) override;
                Status status(
                    ServerContext *context,
                    const Request *request,
                    Reply *reply
                ) override;
            };
        }
    }
}

#endif //GLIAD_SERVER_H
