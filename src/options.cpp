#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

using namespace std;
namespace po = boost::program_options;

class Options {
public:
    string fname;
    double threshold;
    bool negate_threshold;

    bool parse(int argc, char *argv[]) {
        vector<string> config_fnames;

        po::options_description positional("positional arguments");
        positional.add_options()
            ("fname", po::value<string>(&fname), "filename");

        po::positional_options_description p;
        p.add("fname", -1);

        po::options_description optional("optional arguments");
        optional.add_options()
            ("help,h", "Display help message")
            ("config", po::value<vector<string>>(&config_fnames), "Config file where options may be specified (can be specified more than once)")
            ("threshold,t", po::value<double>(&threshold)->default_value(0.25), "Threshold value")
            ("negate-threshold,t", po::bool_switch(&negate_threshold), "Negate threshold");

        po::options_description desc;
        desc.add(positional);
        desc.add(optional);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);

        if (vm.count("help")) {
            cout << make_usage_string_(basename_(argv[0]), optional, p) << '\n';
            return false;
        }

        if (vm.count("config") > 0) {
            config_fnames = vm["config"].as<vector<string> >();

            for (size_t i = 0; i < config_fnames.size(); ++i) {
                ifstream ifs(config_fnames[i].c_str());

                if (ifs.fail()) {
                    cerr << "Error opening config file: " << config_fnames[i] << endl;
                    return false;
                }

                po::store(po::parse_config_file(ifs, desc), vm);
            }
        }


        po::notify(vm);

        return true;
    }

private:
    string basename_(const string &p) {
#ifdef HAVE_BOOST_FILESYSTEM
        return boost::filesystem::path(p).stem().string();
#else
        size_t start = p.find_last_of("/");
        if (start == string::npos)
            start = 0;
        else
            ++start;
        return p.substr(start);
#endif
    }

    // Boost doesn't offer any obvious way to construct a usage string
    // from an infinite list of positional parameters.  This hack
    // should work in most reasonable cases.
    vector<string> get_unlimited_positional_args_(
        const po::positional_options_description &p) {
        assert(p.max_total_count() == numeric_limits<unsigned>::max());

        vector<string> parts;

        // reasonable upper limit for number of positional options:
        const int MAX = 1000;
        string last = p.name_for_position(MAX);

        for (size_t i = 0; true; ++i) {
            string cur = p.name_for_position(i);
            if (cur == last) {
                parts.push_back(cur);
                parts.push_back('[' + cur + ']');
                parts.push_back("...");
                return parts;
            }
            parts.push_back(cur);
        }
        return parts; // never get here
    }

    string make_usage_string_(const string &program_name, const po::options_description &desc, po::positional_options_description &p) {
        vector<string> parts;
        parts.push_back("usage: ");
        parts.push_back(program_name);
        size_t N = p.max_total_count();
        if (N == numeric_limits<unsigned>::max()) {
            vector<string> args = get_unlimited_positional_args_(p);
            parts.insert(parts.end(), args.begin(), args.end());
        } else {
            for (size_t i = 0; i < N; ++i) {
                parts.push_back(p.name_for_position(i));
            }
        }
        if (desc.options().size() > 0) {
            parts.push_back("[options]");
        }
        ostringstream oss;
        copy(
            parts.begin(),
            parts.end(),
            ostream_iterator<string>(oss, " "));
        oss << '\n' << desc;
        return oss.str();
    }
};