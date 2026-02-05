#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "time/time.hpp"
#include "club/club.hpp"

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

    if (!iStream || (iStream >> rest) || (start >= end)) {
        std::cerr << line << '\n';
        return 1;
    }

    int price = 0;

    std::getline(file, line);
    iStream = std::istringstream(line);
    iStream >> price;

    if (!iStream || (price <= 0) || (iStream >> rest)) {
        std::cerr << line << '\n';
        return 1;
    }

    std::vector<std::unique_ptr<novokhatskiy::ClientEvent>> events;
    events.push_back(std::make_unique<novokhatskiy::ClientEvent>());

    while (std::getline(file, line)) {
        iStream = std::istringstream(line);
        auto event = std::make_unique<novokhatskiy::ClientEvent>();
        iStream >> event;

        if ((!iStream) || (iStream >> rest)) {
            std::cerr << line << '\n';
            return 1;
        }

        if (typeid(*event) == typeid(novokhatskiy::ClientSatEvent)) {
            size_t table = dynamic_cast<novokhatskiy::ClientSatEvent&>(*event).getTable();
            if (table > numTables) {
                std::cerr << line << '\n';
                return 1;
            }
        }
        events.push_back(std::move(event));
    }
    file.close();

    novokhatskiy::ComputerClub club(numTables, {start, end}, price, &std::cout);
    for (auto iter = events.begin() + 1; iter != events.end(); ++iter)
        club.executeEvent(**iter);

    return 0;
}
