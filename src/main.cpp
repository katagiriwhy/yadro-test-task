#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Invalid input arguments" << '\n';
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file) {
        std::cerr << "Can't open the file" << '\n';
        return 1;
    }

    std::string line = "";
    std::string rest = "";
    std::getline(file, line);

    std::istringstream iStream(line);

    int numTables = 0;
    iStream >> numTables;
    std::cout << numTables;
    if (!iStream || (numTables <= 0) || (iStream >> rest)) {
        std::cerr << line << '\n';
        return 1;
    }



    return 0;
}
