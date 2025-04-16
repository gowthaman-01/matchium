#pragma once

#include <string_view>

/**
 * @brief Extracts the filename from a full path.
 *
 * It works across platforms by checking for both Unix-style '/' and Windows-style '\\' separators.
 *
 * @param path The full file path (e.g., "/a/b/file.cpp" or "C:\\Users\\file.cpp").
 * @return A string_view representing just the filename (e.g., "file.cpp").
 */
inline std::string_view get_filename(std::string_view path) {
    // Find the last occurrence of either '/' (Unix) or '\\' (Windows).
    size_t pos = path.find_last_of("/\\");

    // If no slashes found, return the entire input (it's already a filename).
    // Otherwise, return the substring that starts after the last slash.
    return (pos == std::string_view::npos) ? path : path.substr(pos + 1);
}

