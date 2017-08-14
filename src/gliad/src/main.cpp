#include "glia/common/logging.h"
#include "glia/gliad/global.h"
#include "glia/gliad/app.h"

void handler(int) {
    try {
        glia::gliad::exit.set_value();
    } catch (const future_error &err) {
        LOG(warning) << "something is going on.";
    }
}

int main(int argc, char *argv[]) {
    glia::gliad::Options options;
    if (!options.parse(argc, argv)) {
        return EXIT_FAILURE;
    }

    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    signal(SIGQUIT, handler);

    glia::gliad::Application app(options);
    app.start();
    return EXIT_SUCCESS;
}