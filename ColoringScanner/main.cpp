#include "impl/Scanner.h"


int main() {
    Scanner scanner;
    scanner.read_tokens("../data/tokens.csv");
    scanner.parse_file("../data/text.txt");
}
