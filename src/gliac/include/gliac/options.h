#include "glia/common/options.h"
#include <string>

#ifndef GLIAC_OPTIONS_H
#define GLIAC_OPTIONS_H

#include "glia/common/options.h"
#include <string>

using namespace std;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"
namespace po = boost::program_options;
#pragma clang diagnostic pop

namespace gliac {
    class Options : glia::common::Options {
    public:
        string host;
        int port;

        bool parse(int argc, char *argv[]) override;
    };
}

#endif //GLIAC_OPTIONS_H
