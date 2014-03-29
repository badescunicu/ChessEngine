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
    void log_binary(const void* source, const int size);
    std::ofstream out;

    ~Logger();
private:
    // Name of the log_file, it defaults to "log.txt"
    std::string log_file;
    // Name to prefix the log messages.
    // It defaults to "[General]".
    std::string prefix;
};

#endif
