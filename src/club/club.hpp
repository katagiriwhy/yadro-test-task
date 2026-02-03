#ifndef COMPUTER_CLUB_CLUB_HPP
#define COMPUTER_CLUB_CLUB_HPP
#include <queue>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>
#include <ostream>

#include "time/time.hpp"

namespace novokhatskiy {
    struct Table {
        Time busyFrom{};
        size_t income = 0;
        size_t busyMinutes = 0;
    };

    class ComputerClub {
    public:
        ComputerClub(size_t tables, std::pair<Time, Time> workingTime, size_t price, std::ostream* output);
        void addClient(const std::string& client);
        void addClientToQueue(const std::string& client);

    private:
        size_t _numTables;
        std::ostream* _output;
        std::pair<Time, Time> _workingTime;
        size_t _price;
        std::set<std::string> _clients;
        std::queue<std::string> _waitingClients;
        std::unordered_map<size_t, Table> _tables;
    };
}

#endif
