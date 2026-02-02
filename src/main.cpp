#include <iostream>
#include <fstream>
#include <string>

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



    return 0;
}
