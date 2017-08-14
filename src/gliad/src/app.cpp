#include "glia/common/logging.h"
#include "glia/gliad/global.h"
#include "glia/gliad/app.h"

glia::gliad::Application::Application(glia::gliad::Options &options) {
    this->options = &options;

    Document doc(kObjectType);
    doc.AddMember(StringRef("length"), Value(11), doc.GetAllocator());
    doc.AddMember(StringRef("delay"), Value(4536), doc.GetAllocator());

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    LOG(debug)
        << logging::add_value("Extra", buffer.GetString())
        << "hello little world";

    LOG(info)
        << logging::add_value("Extra", buffer.GetString())
        << "hello little world";

    LOG(warning)
        << logging::add_value("Extra", buffer.GetString())
        << "hello little world";

    LOG(error)
        << logging::add_value("Extra", buffer.GetString())
        << "hello little world";

    LOG(fatal)
        << logging::add_value("Extra", buffer.GetString())
        << "hello little world";
}

glia::gliad::Application::~Application() {
    while (!ports.empty()) {
        int *port = ports.back();
        ports.pop_back();
        delete port;
    }
}

void glia::gliad::Application::start() {
    this->handlers.emplace_back(thread([=] { server_thread(); }));
    this->handlers.emplace_back(thread([=] { client_thread(); }));

    for (auto &thread : handlers) {
        thread.join();
    }
}

void glia::gliad::Application::server_thread() {
    auto runner = [&]() { server->Wait(); };

    ServerBuilder builder;
    glia::gliad::services::Server service;

    for (auto &addr : this->options->bind) {
        int *port = new int;
        ports.emplace_back(port);
        builder.AddListeningPort(addr, grpc::InsecureServerCredentials(), port);
    }

//    builder.SetSyncServerOption(ServerBuilder::NUM_CQS, 1);
    builder.RegisterService(&service);
    server = builder.BuildAndStart();
    thread runner_thread(runner);
    auto future = glia::gliad::exit.get_future();
    future.wait();
    server->Shutdown();
    runner_thread.join();
}

void glia::gliad::Application::client_thread() {
    for (int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (auto &port : this->ports) {
            cout << "port: " << to_string(*port) << endl;
        }
    }
}