#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <regex>
#include <format>

struct Token {
    std::string name;
    std::regex regex;
    std::string description;
    std::string color;
    std::string  regex_pattern;
    
    void print() {
        std::cout<<std::format("{} {} {} {} \n", name, regex_pattern, description, color);
    }
};

class Scanner {
public:
    void read_tokens(const std::string& path);
    void parse_file(const std::string& path);
    
private:
    std::string parse_line(const std::string& line);
    std::vector<Token> tokens;
};