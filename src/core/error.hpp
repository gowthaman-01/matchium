#pragma once

#include <string>

class Error {
public:
    /**
     * @brief Logs a system error and exits the program.
     *
     * @param label Message prefix for perror (e.g., "bind")
     * @param fd File descriptor to close before exiting (optional; pass -1 to skip)
     */
    static void fatal(const std::string& label, int fd = -1);
};
