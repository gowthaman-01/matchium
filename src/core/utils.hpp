#pragma once

#include "constants.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <vector>

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
inline std::string get_filename(std::string path) {
    // Find the last occurrence of either '/' (Unix) or '\\' (Windows).
    size_t pos = path.find_last_of("/\\");
   
    // If no slashes found, return the entire input (it's already a filename).
    // Otherwise, return the substring that starts after the last slash.
    return (pos == std::string_view::npos) ? path : path.substr(pos + 1);
}

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
inline std::string format_identity(Constants::Role role, int fd) {
    return "[" + Constants::to_string(role) + " " + std::to_string(fd) + "]";
}

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
inline std::string pad_content(const std::string& content, std::size_t width = Constants::padding_width) {
    if (content.length() >= width) return content;
    return content + std::string(width - content.length(), ' ');
}

/**
 * @brief Splits a string view into a vector of strings based on a delimiter.
 *
 * @param str The input string view to split.
 * @param delimiter The delimiter used to split the string.
 * @return A vector of strings representing the split substrings.
 */
inline std::vector<std::string> split(std::string_view str, std::string_view delimiter) {
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    std::vector<std::string> split_strs;
    
    while (end != std::string::npos) {
        split_strs.emplace_back(str.substr(start, end - start));
        
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    
    // Add the last remaining piece
    if (start < str.size()) {
        split_strs.emplace_back(str.substr(start));
    }
    
    return split_strs;
}

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
inline std::pair<std::string, std::string> split_once(std::string_view str, std::string_view delimiter) {
    size_t pos = str.find(delimiter);
    if (pos == std::string::npos) {
        return {std::string(str), ""};  // No delimiter found → return whole string as key
    }
    
    std::string key = std::string(str.substr(0, pos));
    std::string value = std::string(str.substr(pos + delimiter.length()));
    
    return {key, value};
}
