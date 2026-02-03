#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "time/time.hpp"

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
    if (!iStream || (numTables <= 0) || (iStream >> rest)) {
        std::cerr << line << '\n';
        return 1;
    }
    std::getline(file, line);
    iStream = std::istringstream(line);

    novokhatskiy::Time start{};
    novokhatskiy::Time end{};

    iStream >> start >> end;

    int price = 0;

    std::getline(file, line);
    iStream = std::istringstream(line);
    iStream >> price;

    if (!iStream || (price <= 0) || iStream >> rest) {
        std::cerr << line << '\n';
        return 1;
    }


    return 0;
}
