#include "club.hpp"

#include <utility>

novokhatskiy::ComputerClub::ComputerClub(size_t tables, std::pair<Time, Time> workingTime, size_t price,
std::ostream* output) :
    _numTables(tables),
    _workingTime(std::move(workingTime)),
    _price(price),
    _output(output),
    _tables(),
    _clients(),
    _waitingClients()
{
    _tables.reserve(tables);

    for (size_t i = 0; i < tables; ++i)
        _tables[i + 1] = Table{};
    (*output) << workingTime.first;
}

void novokhatskiy::ComputerClub::addClient(const std::string &client) {
    _clients.insert(client);
}

void novokhatskiy::ComputerClub::addClientToQueue(const std::string &client) {
    _waitingClients.push(client);
}

