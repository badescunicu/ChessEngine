#include <fstream>
#include <iomanip>
#include <logger.hpp>

Logger::Logger(const std::string log_file, const std::string prefix) {
    this->log_file = log_file;
    this->prefix = prefix;
    out.open(log_file.c_str(), std::ofstream::out | std::ofstream::trunc);
}

void Logger::log(const std::string message) {
    out << prefix << message << std::endl;
}

void Logger::log(const int number) {
    out << prefix << number << std::endl;
}
