#include <fstream>
#include <iomanip>
#include <logger.hpp>

Logger::Logger(const std::string log_file, const std::string prefix) {
    this->log_file = log_file;
    this->prefix = prefix;
    out.open(log_file.c_str(), std::ofstream::out | std::ofstream::trunc);
}

Logger::~Logger() {
    out.close();
}

void Logger::log(const std::string message) {
    out << prefix << message << std::endl;
}

void Logger::log(const int number) {
    out << prefix << number << std::endl;
}

void Logger::log_binary(const void* source, const int size) {
    const char *byte = static_cast<const char*>(source);
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            if ((byte[i] >> j) & 1) {
                out << "1";
            } else {
                out << "0";
            }
        }
    }
    out << std::endl;
}

