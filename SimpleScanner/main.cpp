#include <iostream>
#include <utility>
#include <format>

class Scanner {
    int index;
    std::string input;
    
    std::string scan_number() {
        std::string result = "(Number, ";
        while(index < input.size() && input[index] >= '0' && input[index] <= '9') {
            result += input[index];
            index++;
        }
        if (index < input.size() && input[index] == '.') {
            result += input[index];
            index++;
            if (index >=  input.size() ||input[index] < '0' || input[index] > '9') 
                throw std::invalid_argument(std::format("Invalid token at position {}", index));
            
            while(index < input.size() && input[index] >= '0' && input[index] <= '9') {
                result += input[index];
                index++;
            }
        }
        if (index < input.size() && input[index] == 'e' || input[index] == 'E' ) {
            result += input[index];
            index++;
            if (index >= input.size() || input[index] < '0' || input[index] > '9')
                throw std::invalid_argument(std::format("Invalid token at position {}", index));

            while(index < input.size() && input[index] >= '0' && input[index] <= '9') {
                result += input[index];
                index++;
            }
        }
        index--;
        return result + ")";
    }
    
    std::string scan_identifier() {
        std::string result = "(Identifier, " ;
        
        while(index < input.size() && (input[index] >= 'a' && input[index] <= 'z') || (input[index] >= 'A' && input[index] <= 'Z')) {
            result += input[index];
            index++;
        }
        index--;
        
        return result + ")";;
    }
    
public:
    explicit Scanner(std::string input) : index(-1), input(std::move(input)) {};
    
    std::string scan() {
        index++;
        if (index == input.size()) throw std::invalid_argument("No more tokens!");
        
        if (input[index] == '+') return {"(Plus, +)"};
        else if(input[index] == '-') return {"(Minus, -)"};
        else if(input[index] == '*') return {"(Star, *)"};
        else if(input[index] == '/') return {"(Slash, /)"};
        else if(input[index] == '(') return {"(LParen, ()"};
        else if(input[index] == ')') return {"(RParen, )"};
        else if(input[index] >= '0' && input[index] <= '9') return scan_number();
        else if ((input[index] >= 'a' && input[index] <= 'z') || (input[index] >= 'A' && input[index] <= 'Z')) return scan_identifier();
        else throw std::invalid_argument(std::format("Invalid token at position {}", index));
    }
};

int main() {
    Scanner scanner("1..234E451+234.1234e56+identifier-/1234abcderfsafb");

    try {
        while (true) {
            std::cout << scanner.scan() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}