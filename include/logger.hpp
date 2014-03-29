#ifndef __LOGGER__HPP
#define __LOGGER__HPP

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string log_file = "log.txt",
           const std::string prefix = "[General] ");
    void log(const std::string message);
    void log(const int number);
    // The raw version does not print prefix and endl
    void log_raw(const std::string message);
    void log_raw(const int number);
    std::ofstream out;
private:
    // Name of the log_file, it defaults to "log.txt"
    std::string log_file;
    // Name to prefix the log messages.
    // It defaults to "[General]".
    std::string prefix;
};

#endif
