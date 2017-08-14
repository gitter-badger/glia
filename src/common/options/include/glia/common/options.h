#ifndef GLIA_COMMON_OPTIONS_H
#define GLIA_COMMON_OPTIONS_H

#include <boost/program_options/options_description.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace glia{
    namespace common {
        namespace po = boost::program_options;

        class Options {
        public:
            virtual bool parse(int argc, char *argv[]) = 0;

        protected:
            string basename(const string &path);

            vector<string> parse_unlimited(
                const po::positional_options_description &pdesc,
                unsigned int upper_max
            );

            string usage(
                const string &program_name,
                const po::options_description &desc,
                const po::positional_options_description &pdesc
            );

        };
    }
}

#endif //GLIA_COMMON_OPTIONS_H
