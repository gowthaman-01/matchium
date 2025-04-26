#include "../../include/core/utils.hpp"

#include "../../include/core/constants.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <vector>


namespace Utility {
    std::string get_filename(std::string path) {
        // Find the last occurrence of either '/' (Unix) or '\\' (Windows).
        size_t pos = path.find_last_of("/\\");
        
        // If no slashes found, return the entire input (it's already a filename).
        // Otherwise, return the substring that starts after the last slash.
        return (pos == std::string_view::npos) ? path : path.substr(pos + 1);
    }

    std::string format_identity(Constants::Role role, int fd) {
        return "[" + Constants::to_string(role) + " " + std::to_string(fd) + "]";
    }

    std::string pad_content(const std::string& content, std::size_t width) {
        if (content.length() >= width) return content;
        return content + std::string(width - content.length(), ' ');
    }

    std::vector<std::string> split(std::string_view str, std::string_view delimiter) {
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

    std::pair<std::string, std::string> split_once(std::string_view str, std::string_view delimiter) {
        size_t pos = str.find(delimiter);
        if (pos == std::string::npos) {
            return {std::string(str), ""};  // No delimiter found → return whole string as key
        }
        
        std::string key = std::string(str.substr(0, pos));
        std::string value = std::string(str.substr(pos + delimiter.length()));
        
        return {key, value};
    }
}
