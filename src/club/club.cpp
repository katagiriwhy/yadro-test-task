#include "club.hpp"

#include <utility>

novokhatskiy::ComputerClub::ComputerClub(size_t tables, std::pair<Time, Time> workingTime, size_t price,
std::ostream* output) :
    _numTables(tables),
    _workingTime(std::move(workingTime)),
    _currentTime(),
    _price(price),
    _output(output),
    _tables(),
    _clients(),
    _waitingClients()
{
    _tables.reserve(tables);

    for (size_t i = 0; i < tables; ++i)
        _tables[i + 1] = Table{};
    (*output) << workingTime.first << '\n';
}

novokhatskiy::ComputerClub::~ComputerClub() {
    (*_output) << _workingTime.second << '\n';
}

void novokhatskiy::ComputerClub::addClient(const std::string &client) {
    _clients.insert(client);
}

void novokhatskiy::ComputerClub::addClientToQueue(const std::string &client) {
    _waitingClients.push(client);
}

bool novokhatskiy::ComputerClub::hasAvailableTable() const {
    for (const auto& [_, table] : _tables) {
        if (!table.client)
            return true;
    }
    return false;
    //return _tables.size() < _numTables;
}

bool novokhatskiy::ComputerClub::isTableTaken(size_t table) const {
    auto it = _tables.find(table);
    return it != _tables.end() && it->second.client.has_value();
    //return _tables.find(table) != _tables.cend();
}

bool novokhatskiy::ComputerClub::isOpen() const {
    return (_workingTime.first <= _currentTime) && (_currentTime < _workingTime.second);
}

size_t calculateHoursDiff(novokhatskiy::Time after, novokhatskiy::Time before) {
    novokhatskiy::Time diff = after - before;
    return diff.hours + ((diff.minutes != 0) ? 1 : 0);
}

size_t novokhatskiy::ComputerClub::updateIncome(const std::string &name) {
    for (auto& [tableNum, table] : _tables) {
        if (table.client && *table.client == name) {

            Time diff = _currentTime - table.busyFrom;

            table.busyMinutes += diff.hours * 60 + diff.minutes;

            size_t hours = calculateHoursDiff(_currentTime, table.busyFrom);
            table.income += hours * _price;

            table.client.reset();

            return tableNum;
        }
    }
    return 0;
}

bool novokhatskiy::ComputerClub::isQueueEmpty() const {
    return _waitingClients.empty();
}

novokhatskiy::Time novokhatskiy::ComputerClub::getCurrentTime() const {
    return _currentTime;
}

void novokhatskiy::ComputerClub::printEvent(const novokhatskiy::Event &event) const {
    (*_output) << event << '\n';
}

bool novokhatskiy::ComputerClub::hasClient(const std::string &name) const {
    return (_clients.find(name) != _clients.cend());
}

void novokhatskiy::ComputerClub::assignTable(const std::string &name, size_t table) {
    updateIncome(name);

    auto& tmp = _tables.at(table);
    tmp.client = name;
    tmp.busyFrom = _currentTime;
}

size_t novokhatskiy::ComputerClub::removeClient(const std::string &name) {
    size_t table = updateIncome(name);
    if (isOpen()) {
        _clients.erase(name);
    }
    return table;
}

std::string novokhatskiy::ComputerClub::getClientFromQueue() {
    std::string name = std::move(_waitingClients.front());
    _waitingClients.pop();
    return name;
}

