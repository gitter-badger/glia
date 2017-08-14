#ifndef GLIAC_APPLICATION_H
#define GLIAC_APPLICATION_H

#include "gliac/options.h"

namespace gliac {
    class Application {
    public:
        explicit Application(gliac::Options &options);
        ~Application();

        void run();

    private:
        void server_thread();
        void client_thread();

        gliac::Options *options;
    };
}

#endif //GLIAC_APPLICATION_H
