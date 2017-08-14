#ifndef GLIAD_OPTIONS_H
#define GLIAD_OPTIONS_H

#include "glia/common/options.h"
#include <boost/bind.hpp>
#include <string>

using namespace std;
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"
namespace po = boost::program_options;
#pragma clang diagnostic pop

namespace glia {
    namespace gliad {
        namespace defaults {
            static const string bind = "127.0.0.1:8847";
        };

        class Options : glia::common::Options {
        public:
            vector<string> bind;

            bool parse(int argc, char *argv[]) override;

        private:
            void on_bind(vector<string> bind);
        };
    }
}

#endif //GLIAD_OPTIONS_H