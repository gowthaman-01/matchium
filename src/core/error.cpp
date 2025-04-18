#include "error.hpp"

#include <cstdlib>
#include <string>

#include <unistd.h>

void Error::fatal(const std::string& label, int fd) {
    /**
     * DESIGN NOTE:
     * Using const std::string& instead of std::string_view here because perror()
     * requires a null-terminated C-string (const char*).
     *
     * std::string_view does not guarantee null-termination, so we'd have to
     * create a temporary std::string anyway — introducing an unnecessary heap
     * allocation just to log the error.
     */
    
    perror(label.c_str());
    
    if (fd >= 0) {
        close(fd);
    }
    
    std::exit(1);
}
