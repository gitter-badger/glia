#include "glia/gliad/services/server.h"

Status glia::gliad::services::Server::gossip(
    ServerContext *context,
    const Request *request,
    Reply *reply
) {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->message());
    return Status::OK;
}

Status glia::gliad::services::Server::status(
    ServerContext *context,
    const Request *request,
    Reply *reply
) {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->message());
    return Status::OK;
}