#include "event_handler.hpp"
#include <string>
#include <algorithm>
#include "club/club.hpp"

std::string ErrorToString(novokhatskiy::ErrorType e) {
    using namespace novokhatskiy;
    switch (e) {
        case ErrorType::NotOpenYet: return "NotOpenYet";
        case ErrorType::YouShallNotPass: return "YouShallNotPass";
        case ErrorType::ClientUnknown: return "ClientUnknown";
        case ErrorType::PlaceIsBusy: return "PlaceIsBusy";
        case ErrorType::ICanWaitNoLonger: return "ICanWaitNoLonger!";
    }

    return "";
}

void novokhatskiy::Event::print(std::ostream& out) const {
    out << _time << ' ' << _id;
}

void novokhatskiy::Event::execute(novokhatskiy::ComputerClub &club) const {
    club.printEvent(*this);
}

novokhatskiy::Time novokhatskiy::Event::getTime() const {
    return _time;
}

novokhatskiy::Event::Event(novokhatskiy::Time time, novokhatskiy::EventType type) :
    _id(0),
    _type(type),
    _time(time)
{}

novokhatskiy::ErrorEvent::ErrorEvent(novokhatskiy::Time time, novokhatskiy::ErrorType error) :
Event(time, EventType::Outcoming),
_error(error)
{
    _id = 13;
}

void novokhatskiy::ErrorEvent::print(std::ostream &out) const {
    Event::print(out);
    out << ' ' << ErrorToString(_error);
}

bool isValidName(const std::string& name) {
    if (name.empty()) {
        return false;
    }

    constexpr auto pred = [] (unsigned char c) {
        return (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == '_' ||
        c == '-';
    };

    return std::all_of(name.cbegin(), name.cend(), pred);
}

std::istream &novokhatskiy::operator>>(std::istream &in, std::unique_ptr<ClientEvent> &event) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    unsigned short id = 0;
    Time time{};
    std::string name = "";

    in >> time >> id >> name;
    if (!in) {
        return in;
    }

    if (!isValidName(name)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    switch (id) {
        case 1:
            event = std::make_unique<ClientEnteredEvent>(time, name);
            break;

        case 2: {
            size_t table = 0;
            in >> table;
            if (in && (table > 0)) {

            }
            break;
        }


//        case 3:
//
//            break;
//
//        case 4:
//
//            break;
        default:
            in.setstate(std::ios::failbit);
            break;
    }

    return in;
}

std::ostream &novokhatskiy::operator<<(std::ostream &out, const novokhatskiy::Event &event) {
    event.print(out);
    return out;
}

novokhatskiy::ClientEvent::ClientEvent(Time time, EventType type, const std::string& name) :
    Event::Event(time, type),
    _name(name)
{}

void novokhatskiy::ClientEvent::print(std::ostream &out) const {
    Event::print(out);
    out << ' ' << _name;
}

novokhatskiy::ClientEnteredEvent::ClientEnteredEvent(novokhatskiy::Time time, const std::string &name) :
    ClientEvent(time, EventType::Incoming, name)
{
    _id = 1;
}

void novokhatskiy::ClientEnteredEvent::execute(novokhatskiy::ComputerClub &club) const {
    Event::execute(club);
    if (!club.isOpen()) {
        ErrorEvent(club.getCurrentTime(), ErrorType::NotOpenYet).execute(club);
    } else if (club.hasClient(_name)) {
        ErrorEvent(club.getCurrentTime(), ErrorType::YouShallNotPass).execute(club);
    } else {
        club.addClient(_name);
    }
}

novokhatskiy::ClientSatEvent::ClientSatEvent(novokhatskiy::Time time, const std::string &name, size_t table,
                                             novokhatskiy::EventType type) :
        ClientEvent(time,type,name),
        _table(table)
{
    if (type == EventType::Incoming) {
        _id = 2;
    } else {
        _id = 12;
    }
}

size_t novokhatskiy::ClientSatEvent::getTable() const {
    return _table;
}

void novokhatskiy::ClientSatEvent::print(std::ostream &out) const {
    ClientEvent::print(out);
    out << ' ' << _table;
}

void novokhatskiy::ClientSatEvent::execute(novokhatskiy::ComputerClub &club) const {
    Event::execute(club);
    if (_type == EventType::Incoming) {
        if (!club.hasClient(_name)) {
            ErrorEvent(club.getCurrentTime(), ErrorType::ClientUnknown).execute(club);
            return;
        }
        if (club.isTableTaken(_table)) {
            ErrorEvent(club.getCurrentTime(), ErrorType::PlaceIsBusy).execute(club);
            return;
        }
    }
    club.assignTable(_name, _table);
}


novokhatskiy::ClientWaitingEvent::ClientWaitingEvent(novokhatskiy::Time time, const std::string &name) {

}

void novokhatskiy::ClientWaitingEvent::execute

(novokhatskiy::ComputerClub &club) const {

}
