#include "logging.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
glia::common::Logging glia::common::logger;

glia::common::Logging::Logging() {
    typedef sinks::synchronous_sink <sinks::text_ostream_backend> text_sink;
    boost::shared_ptr<text_sink> sink(new text_sink);

    text_sink::locked_backend_ptr backend = (*(&sink))->locked_backend();

    boost::shared_ptr<ostream> console(&clog, boost::null_deleter());
    (*(&backend))->add_stream(console);

    (*(&sink))->set_formatter(&formatter);

    boost::shared_ptr<logging::core> core = logging::core::get();

    core->add_sink((*(&sink)));

    core->add_global_attribute("TimeStamp", attrs::local_clock());
}

auto &glia::common::Logging::get() {
    return this->slg;
}

void glia::common::Logging::formatter(
    const logging::record_view &record,
    logging::formatting_ostream &stream
) {
    switch (record[logging::trivial::severity].get()) {
        case severity_level::debug:
            stream << "\033[94m";
            break;
        case severity_level::info:
            stream << "\033[0m";
            break;
        case severity_level::warning:
            stream << "\033[93m";
            break;
        case severity_level::error:
            stream << "\033[91m";
            break;
        case severity_level::fatal:
            stream << "\033[101m";
            break;
    }

    Document doc(kObjectType);
    auto &allocator = doc.GetAllocator();

    auto timestamp = logging::extract<ptime>("TimeStamp", record);
    doc.AddMember(
        Value("timestamp", allocator),
        Value(to_simple_string(timestamp.get()).c_str(), allocator),
        allocator
    );

    doc.AddMember(
        Value("severity", allocator),
        Value(to_string(record[logging::trivial::severity].get()), allocator),
        allocator
    );

    auto extra = logging::extract<string>("Extra", record);
    if (extra) {
        Document d;
        d.Parse(extra.get().c_str());
        for (auto &m : d.GetObject()) {
            doc.AddMember(
                Value(m.name.GetString(), allocator),
                Value(m.value, allocator),
                allocator
            );
        }
    }

    doc.AddMember(
        Value("message", allocator),
        Value(string(record[exprs::smessage].get()).c_str(), allocator),
        allocator
    );

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    stream << buffer.GetString();
    stream << "\033[0m";
}