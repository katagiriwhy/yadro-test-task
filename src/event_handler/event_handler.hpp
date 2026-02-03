#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <memory>

#include "time/time.hpp"
#include "club/club.hpp"

namespace novokhatskiy {

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
        virtual void execute(const novokhatskiy::ComputerClub& club) const;
    protected:
        unsigned short _id;
        EventType _type;
        Time _time;
    };

    class ClientEvent : public Event {
    public:
        ClientEvent() = default;
        ClientEvent(Time time, const std::string& name);
        virtual void print(std::ostream& out) const override;
    protected:
        std::string _name;
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
