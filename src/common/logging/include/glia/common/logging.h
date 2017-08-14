#ifndef GLIA_COMMON_LOGGING_H
#define GLIA_COMMON_LOGGING_H

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/make_shared.hpp>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <mstch/mstch.hpp>
#include <iostream>

using namespace std;

namespace logging = boost::log;
namespace srcs = logging::sources;
namespace exprs = logging::expressions;
namespace sinks = logging::sinks;
namespace attrs = logging::attributes;
namespace keywords = logging::keywords;
namespace trivial = logging::trivial;

#define LOG(lvl) BOOST_LOG_SEV(glia::common::logger::get(), trivial::lvl)

namespace glia {
    namespace common {
        using namespace srcs;
        using namespace trivial;
        using namespace rapidjson;
        using namespace boost::posix_time;

        class Logging {
        public:
            Logging();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
            auto &get();
#pragma clang diagnostic pop

        private:
            severity_logger_mt<severity_level> slg;

            static void formatter(
                logging::record_view const &rec,
                logging::formatting_ostream &strm
            );
        };

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
        extern Logging logger;
#pragma clang diagnostic pop
    }
}

#endif //GLIA_COMMON_LOGGING_H
