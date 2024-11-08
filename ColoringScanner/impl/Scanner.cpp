#include <unordered_set>
#include "Scanner.h"

void Scanner::read_tokens(const std::string& path) {
    std::ifstream stream(path);
    std::string line;
    
    while(std::getline(stream, line)) {
        std::stringstream string_stream(line);
        std::string name, pattern, description, color;
        
        std::getline(string_stream, name, ';');
        std::getline(string_stream, pattern, ';');
        std::getline(string_stream, description, ';');
        std::getline(string_stream, color, ';');
        
        tokens.push_back({name, std::regex (pattern), description, color, pattern});
    }
}

std::string Scanner::parse_line(const std::string& line) {
    std::string result;
    std::string line_copy = line;

    while (!line_copy.empty()) {
        bool found = false;
        for (const auto& [name, regex, description, color, regex_pattern] : tokens) {
            std::smatch match;
            if (std::regex_search(line_copy, match, regex)) {
                if (match.position() == 0) {
                    std::string curr_match = match.str();
                    if (name == "FUNCTION" && !curr_match.empty()) {
                        curr_match.pop_back(); 
                    }
                    result += std::format(R"(<span class="word" style="color: {};">{}</span>)", color, curr_match);
                    line_copy = line_copy.substr(curr_match.length());
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            throw std::runtime_error("Unable to parse line: " + line);
        }
    }

    return result;
}

void Scanner::parse_file(const std::string& path) {
    std::ifstream input_file(path);
    std::ofstream output_file("../result.html");

    output_file << "<!DOCTYPE html>\n"
                << "<html lang=\"pl\">\n"
                << "<head>\n"
                << "    <meta charset=\"UTF-8\">\n"
                << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                << "    <title>Colorful parsed text</title>\n"
                << "    <style>\n"
                << "        body {\n"
                << "            background-color: #1E1E1E;\n"
                << "            color: #D4D4D4;\n"
                << "            font-family: 'Consolas', monospace;\n"
                << "        }\n"
                << "        pre {\n"
                << "            white-space: pre-wrap;\n"
                << "        }\n"
                << "    </style>\n"
                << "</head>\n"
                << "<body>\n"
                << "<pre>\n";

    std::string line;
    while (std::getline(input_file, line)) {
        try {
            output_file << parse_line(line) << "\n";
        } catch (...) {
            output_file << R"(<span class="word" style="color: red;">ERROR OCCURRED HERE</span>)";
                    break;
        }
    }

    output_file << "</pre>\n"
                << "</body>\n"
                << "</html>";

    input_file.close();
    output_file.close();

    std::cout << "HTML file generated: result.html" << std::endl;
}
