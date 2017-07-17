#include "options.cpp"

int main(int argc, char *argv[]) {
    Options options;
    if (!options.parse(argc, argv)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}