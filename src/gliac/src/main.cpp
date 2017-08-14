#include "gliac/app.h"

int main(int argc, char *argv[]) {
    gliac::Options options;
    if (!options.parse(argc, argv)) {
        return EXIT_FAILURE;
    }

    gliac::Application app(options);
    // TODO Main try catch needs to be here
    app.run();
    return EXIT_SUCCESS;
}