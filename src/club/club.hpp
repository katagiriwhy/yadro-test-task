#ifndef COMPUTER_CLUB_CLUB_HPP
#define COMPUTER_CLUB_CLUB_HPP
#include <queue>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>
#include <ostream>
#include <optional>

#include "time/time.hpp"
#include "event_handler/event_handler.hpp"


namespace novokhatskiy {
    struct Table {
        std::optional<std::string> client = std::nullopt;
        Time busyFrom{};
        size_t income = 0;
        size_t busyMinutes = 0;
    };

    class ComputerClub {
    public:
        ComputerClub(size_t tables, std::pair<Time, Time> workingTime, size_t price, std::ostream* output);
        ~ComputerClub();

        void addClient(const std::string& client);
        void addClientToQueue(const std::string& client);
        void printEvent(const Event& event) const;
        void assignTable(const std::string& name, size_t table);
        size_t removeClient(const std::string& name);
        std::string getClientFromQueue();

        bool hasClient(const std::string& name) const;
        bool hasAvailableTable() const;
        bool isTableTaken(size_t table) const;
        bool isOpen() const;
        bool isQueueEmpty() const;

        Time getCurrentTime() const;

    private:
        size_t _numTables;
        std::ostream* _output;
        std::pair<Time, Time> _workingTime;
        Time _currentTime;
        size_t _price;
        std::set<std::string> _clients;
        std::queue<std::string> _waitingClients;
        std::unordered_map<size_t, Table> _tables;

        size_t updateIncome(const std::string& name);
    };
}

#endif
