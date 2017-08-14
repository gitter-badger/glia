#ifndef GLIAD_APPLICATION_H
#define GLIAD_APPLICATION_H

#include "options.h"
#include "glia/gliad/services/server.h"
#include <boost/format.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>

namespace glia {
    namespace gliad {
        using namespace rapidjson;

        class Application {
        public:
            unique_ptr<Server> server;

            explicit Application(gliad::Options &options);
            ~Application();
            void start();

        private:
            gliad::Options *options;
            vector<thread> handlers;
            vector<int*> ports;

            void server_thread();
            void client_thread();
        };
    }
}

#endif //GLIAD_APPLICATION_H
