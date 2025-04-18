#pragma once

#include "constants.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace Utility {
    /**
     * @brief Extracts the filename from a full path.
     *
     * It works across platforms by checking for both Unix-style '/' and Windows-style '\\' separators.
     *
     * DESIGN NOTE:
     * We return std::string here (instead of std::string_view) because the result is
     * immediately used in string concatenation (e.g., get_filename(__FILE__) + ":").
     *
     * @param path The full file path (e.g., "/a/b/file.cpp" or "C:\\Users\\file.cpp").
     * @return A string representing just the filename (e.g., "file.cpp").
     */
    std::string get_filename(std::string path);

    /**
     * @brief Formats an identity string for logging.
     *
     * Converts a Role (e.g., Server or Client) and file descriptor into a readable string
     * of the format "[server: 3]" or "[client: 4]", useful for structured logging.
     *
     * DESIGN NOTE:
     * We return std::string here (instead of std::string_view) because the result is
     * immediately used in string concatenation (e.g., server + std::to_string(fd_)).
     *
     * @param role The role of the connection (Server or Client).
     * @param fd   The file descriptor associated with the connection.
     * @return The formatted string.
     */
    std::string format_identity(Constants::Role role, int fd);

    /**
     * @brief Pads the input string with spaces to reach a desired fixed width.
     *
     * - If the input `content` is already equal to or longer than `width`, it is returned unchanged.
     * - If the input is shorter, spaces are appended to its right until it reaches the desired width.
     *
     * DESIGN NOTE:
     * We return std::string here as returning a string_view to a temporary
     * (like from `content + std::string(...)`) would result in a dangling reference.
     *
     * @param content The string to pad.
     * @param width The target width for padding.
     * @return A new string padded with spaces on the right, suitable for aligned output.
     */
    std::string pad_content(const std::string& content, std::size_t width = Constants::padding_width);

    /**
     * @brief Splits a string view into a vector of strings based on a delimiter.
     *
     * @param str The input string view to split.
     * @param delimiter The delimiter used to split the string.
     * @return A vector of strings representing the split substrings.
     */
    std::vector<std::string> split(std::string_view str, std::string_view delimiter);

    /**
     * @brief Splits a string at the first occurrence of a delimiter.
     *
     * If the delimiter is not found, the entire input is returned as the key,
     * and the value is an empty string.
     *
     * @param str The input string to be split.
     * @param delimiter The delimiter to split at (e.g., ": " for HTTP headers).
     * @return A std::pair containing the key and value as std::strings.
     */
    std::pair<std::string, std::string> split_once(std::string_view str, std::string_view delimiter);
}
