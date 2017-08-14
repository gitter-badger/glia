#include "glia/gliad/options.h"

bool glia::gliad::Options::parse(int argc, char *argv[]) {
    po::options_description positional("positional arguments", 120);
//    positional.add_options()
//        ("fname", po::value<string>(&fname), "filename");
//
    po::positional_options_description pdesc;
//    p.add("fname", -1);

    po::options_description optional("optional arguments", 120);
    optional.add_options()
        ("help", "show this help message and exit")
        ("bind,b", po::value<vector<string>>()
             ->multitoken()
             ->default_value(vector<string>({defaults::bind}), defaults::bind)
             ->notifier(boost::bind(&gliad::Options::on_bind, this, _1)),
         "listen for connections on specified the address (e.g. localhost:1234"
             ", 192.168.1.1:31416 etc.)");
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

    po::notify(vm);
    return true;
}

void glia::gliad::Options::on_bind(vector<string> bind) {
    for (auto &addr : bind) {
        this->bind.emplace_back(addr);
        cout << "bind: " << addr << endl;
    }
}