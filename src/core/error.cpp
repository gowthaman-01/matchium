#include "error.hpp"

#include <cstdlib>
#include <unistd.h>

void Error::fatal(const std::string& label, int fd) {
    perror(label.c_str());
    
    if (fd >= 0) {
        close(fd);
    }
    
    std::exit(1);
}
