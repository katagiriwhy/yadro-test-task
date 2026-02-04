#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <memory>

#include "time/time.hpp"

namespace novokhatskiy {

    class ComputerClub;

    enum class EventType {
        Incoming,
        Outcoming,
    };

    enum class ErrorType {
        YouShallNotPass,
        NotOpenYet,
        PlaceIsBusy,
        ClientUnknown,
        ICanWaitNoLonger,
    };

    class Event {
    public:
        Event() = default;
        Event(Time time, EventType type);
        virtual ~Event() = default;

        Time getTime() const;

        virtual void print(std::ostream& out) const;
        virtual void execute(ComputerClub& club) const;
    protected:
        unsigned short _id{};
        EventType _type;
        Time _time{};
    };

    std::ostream& operator<<(std::ostream& out, const Event& event);

    class ClientEvent : public Event {
    public:
        ClientEvent() = default;
        ClientEvent(Time time, EventType type, const std::string& name);
        virtual void print(std::ostream& out) const override;
    protected:
        std::string _name;
    };

    class ClientEnteredEvent : public ClientEvent{
    public:
        ClientEnteredEvent(Time time, const std::string& name);
        virtual void execute(ComputerClub& club) const override;
    };

    class ClientSatEvent : ClientEvent {
    public:
        ClientSatEvent(Time time, const std::string& name, size_t table, EventType type);
        size_t getTable() const;
        virtual void print(std::ostream& out) const override;
        virtual void execute(ComputerClub& club) const override;
    private:
        size_t _table;
    };

    class ClientWaitingEvent: public ClientEvent
    {
    public:
        ClientWaitingEvent(Time time, const std::string& name);
        virtual void execute(ComputerClub& club) const override;
    };


    std::istream& operator>>(std::istream& in, std::unique_ptr<ClientEvent>& event);

    class ErrorEvent : public Event {
    public:
        ErrorEvent(Time time, ErrorType error);
        virtual void print(std::ostream& out) const override;
    private:
        ErrorType _error;
    };
}

#endif
