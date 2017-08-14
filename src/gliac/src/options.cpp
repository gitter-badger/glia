#include "gliac/options.h"

bool gliac::Options::parse(int argc, char *argv[]) {
    vector<string> config_fnames;

    po::options_description positional("positional arguments", 120);
//    positional.add_options()
//        ("fname", po::value<string>(&fname), "filename");
//
    po::positional_options_description pdesc;
//    p.add("fname", -1);

    po::options_description optional("optional arguments", 120);
    optional.add_options()
        ("help", "show this help message and exit")
        ("host,h", po::value<string>(&host)->default_value("127.0.0.1:8847"),
         "listen for connections on specified the network interface");
//        ("port,p", po::value<int>(&port)->default_value(8847),
//         "port number to use for listening to incoming connections");

    po::options_description cmdline;
    cmdline.add(positional);
    cmdline.add(optional);

    po::variables_map vm;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
    po::store(
        po::command_line_parser(argc, argv)
            .options(cmdline)
            .positional(pdesc)
            .run(),
        vm
    );
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ClangTidyInspection"
    if (vm.count("help")) {
        cout << usage(basename(argv[0]), optional, pdesc) << '\n';
        return false;
    }
#pragma clang diagnostic pop

//    if (vm.count("config") > 0) {
//        config_fnames = vm["config"].as<vector<string> >();
//
//        for (auto &config_fname : config_fnames) {
//            ifstream ifs(config_fname.c_str());
//
//            if (ifs.fail()) {
//                cerr << "Error opening config file: " << config_fname << endl;
//                return false;
//            }
//
//            po::store(po::parse_config_file(ifs, cmdline), vm);
//        }
//    }
//
//
    po::notify(vm);
    return true;
}