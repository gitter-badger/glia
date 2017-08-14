#include "options.h"

string glia::common::Options::basename(const string &path) {
    return boost::filesystem::path(path).stem().string();
}

// Boost doesn't offer any obvious way to construct a usage string
// from an infinite list of positional parameters.  This hack
// should work in most reasonable cases.
vector<string> glia::common::Options::parse_unlimited(
    const po::positional_options_description &pdesc,
    unsigned int upper_max = 1000
) {
    assert(pdesc.max_total_count() == numeric_limits<unsigned>::max());

    vector<string> parts;

    // reasonable upper limit for number of positional options:
    const string &last = pdesc.name_for_position(upper_max);
    for (unsigned int i = 0; true; ++i) {
        string cur = pdesc.name_for_position(i);
        if (cur == last) {
            parts.emplace_back(cur);
            parts.emplace_back('[' + cur + ']');
            parts.emplace_back("...");
            return parts;
        }
        parts.emplace_back(cur);
    }
}

string glia::common::Options::usage(
    const string &program_name,
    const po::options_description &desc,
    const po::positional_options_description &pdesc
) {
    vector<string> parts;
    parts.emplace_back("usage: ");
    parts.emplace_back(program_name);
    size_t num = pdesc.max_total_count();
    if (num == numeric_limits<unsigned>::max()) {
        vector<string> args = parse_unlimited(pdesc);
        parts.insert(parts.end(), args.begin(), args.end());
    } else {
        for (unsigned int i = 0; i < num; ++i) {
            parts.emplace_back(pdesc.name_for_position(i));
        }
    }

    for (const auto &i : desc.options()) {
        parts.emplace_back('[' + i->format_name() + ']');
    }
    parts.emplace_back("\n");

    ostringstream oss;
    copy(
        parts.begin(),
        parts.end(),
        ostream_iterator<string>(oss, " ")
    );
    oss << "\n" << desc;
    return oss.str();
}
